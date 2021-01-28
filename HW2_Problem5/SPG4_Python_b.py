from sgp4.api import Satrec
from sgp4.api import jday
from sgp4.api import SGP4_ERRORS
import numpy as np
from matplotlib import pyplot as plt

#TLE for TechEdSat-10 found at http://celestrak.com/NORAD/elements/active.txt
s = '1 45917U 98067RQ  21027.20394625  .00184105  00000-0  13156-3 0  9996';
t = '2 45917  51.6356 307.5412 0007822 124.5543 235.6195 15.72623071 30805';
satellite = Satrec.twoline2rv(s, t);

#Number of iterations for time after 1/27/21
iterate = 300;
alt = np.zeros(iterate)
time = np.zeros(iterate)
i = 0;

#Part a of HW2 Problem 5- find JDates for when satellite crosses these thresholds
time_350 = 0.0;
time_300 = 0.0;
time_100 = 0.0;

for x in time:
    #Set Initial Julian Date to Today https://keisan.casio.com/exec/system/1227779487
    jd = 2459241.0; #Date is January 27, 2021 
    fr = 0.5+(i*0.5);
    time[i] = jd+fr

    #Find Error, Position (km), and Velocity (km/s) of satellite in ECI
    e, r, v = satellite.sgp4(jd, fr);

    #Final Altitude found using Equation from Piazza Post #25
    #Earth's Altitude is 6378 km
    alt[i] = np.linalg.norm(r) - 6378;

    #Update Times for Part a
    if alt[i] < 350 and time_350 == 0.0:
        time_350 = time[i]
    if alt[i] < 300 and time_300 == 0.0:
        time_300 = time[i]
    if alt[i] < 100 and time_100 == 0.0:
        time_100 = time[i]

    #Iterate
    i = i+1;

print("Crosses 350 km at: ", time_350);
print("Crosses 300 km at: ", time_300);
print("Crosses 100 km at: ", time_100);
    
plt.title("Altitude vs Time of TECHEDSAT-10") 
plt.xlabel("Time [JD]") 
plt.ylabel("Altitude [km]") 
plt.plot(time,alt) 
plt.show()

