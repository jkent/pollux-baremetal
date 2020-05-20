#!/usr/bin/env python2

import dp832
import time

dp = dp832.dp832()
dp.Off(1)
time.sleep(0.25)
dp.On(1)
time.sleep(0.25)
