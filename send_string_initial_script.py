import gps_script
import camera_script
import temperature_script
import soil_moisture_script
import humidity_script
import fire_script
import smoke_script


temp=temperature_script()
humd=humidity_script()
rf=rainfall_script()
fire=fire_script()
smoke=smoke_script()
sm=soil_moisture_script()
long,lat=gps_script()
bears,deer,lynx,wolves=camera_script()

string='4000'+'1'+temp+'1'+humd+'1'+rf+'1'+smoke+'1'+fire+'1'+sm+long+lat+bears+deer+lynx+wolves

file_object=open("sending_file.txt","w")
file_object.write(string)
file_object.close()