from sys import stdin, stdout
#while True:
values=[]
string=''
for x in range(32):
    data=stdin.buffer.read(1)
    new_data=str(data)
    new_data=new_data[2:-1]
    string=string+str(new_data)
    if (len(string) >= 4):
        values.append(str.encode(string))
        string=''
stdout.buffer.write(b'device_id: '+values[1]+b' temperature: '+values[2]+b' humidity: '+values[3]+b' soil_moisture: '+values[4]+b' smoke: '+values[5]+b' fire: '+values[6]+b' deer: '+values[7]+b' ')