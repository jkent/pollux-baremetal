import gdb
from subprocess import run
from time import sleep

class DebugUart(gdb.Command):
    '''Debug target with uart loading'''

    class Q(gdb.Command):
        '''Terminate processes and quit GDB'''

        def __init__(self):
            super().__init__('q', gdb.COMMAND_USER)

        def invoke(self, args, tty):
            try:
                gdb.execute('power off', tty)
            except:
                pass

            sleep(0.1)
            run(['killall', 'JLinkGDBServer', 'miniterm.py'])
            gdb.execute('quit', tty)

    def __init__(self):
        super().__init__('debug_uart', gdb.COMMAND_USER)

    def invoke(self, args, tty):
        bin_file = args + '.bin'
        elf_file = args + '.elf'

        try:
            run(['uart_boot.py', bin_file], check=True)
        except:
            gdb.execute('quit', tty)

        DebugUart.Q()

        gdb.execute('file ' + elf_file, tty)
        run(['mate-terminal', '--window', '-e', 'JLinkGDBServer -device ARM9'], check=True)
        run(['mate-terminal', '--tab', '-e', 'miniterm.py /dev/ttyUSB0 115200'], check=True)
        gdb.execute('target remote localhost:2331', tty)

class Power(gdb.Command):
    '''Control power of target'''

    def __init__(self):
        super().__init__('power', gdb.COMMAND_USER)
    
    def invoke(self, args, tty):
        if args not in ['on', 'off']:
            print('on or off expected')
            return

        gdb.execute('set *0xC0019000 = 1', tty)
        if args == 'on':
            gdb.execute('set *0xC0019004 = 0', tty)
            gdb.execute('set *0xC0019008 = 0x80', tty)
            gdb.execute('set *0xC0019008 = 0', tty)
        else:
            gdb.execute('set *0xC0019008 = 0', tty)
            gdb.execute('set *0xC0019004 = 0x80', tty)
            gdb.execute('set *0xC0019004 = 0', tty)
        gdb.execute('set *0xC0019000 = 0', tty)

gdb.execute('set confirm off')
Power()
DebugUart()
