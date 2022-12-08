
#!/usr/bin/env python
import os
import time

cmd = 'C:\Users\33609\Documents\Arduino\sketch_dec8a.ino'

while True:
    result = os.popen(cmd).readline().strip()
    # le resultat est temp=xx.x’C donc on traite le resultat
    # pour ne garder xx.x
    temp = result.split('=')[1].split("'")[0]
    f=open("/tmp/temp_log.dat','a")
    print >>f,("%s,%s"%(time.strftime("%d-%m-%Y %H:%M:%S"), temp))
    f.close()
    time.sleep(60)