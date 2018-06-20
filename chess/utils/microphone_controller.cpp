#include <cstdlib>
#include <string>

using namespace std;

string first_device = "alsa_input.usb-C-Media_Electronics_Inc._USB_PnP_Sound_Device-00.analog-mono";
string second_device = "alsa_input.pci-0000_00_1f.3.analog-stereo";

void choose_device(int turn){
  string device_name;
  if(!turn){
    device_name = first_device;
  }else{
    device_name = second_device;
  }

  string command = "pacmd set-default-source $(pactl list short sources | grep " +
                    device_name + " | awk '{print $1}')";

  system(command.c_str());
}
