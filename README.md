# Hermes-Lite-2-Xiegu-interface

Written by Vince Vielhaber - K8ZW.
 
 This software is free to use as you wish.  There are no guarantees,
 warranties or promises to it's usefulness.  
 
 Outputs D2-D8 are to switch the filters of a Kenwood TS-440
 board.   The Kenwood needs 12V to switch the relays (2 per band)
 so some kind of buffering is needed.  I'm using a Toshiba TD62783AP
 to drive the relays, Yaesu used this IC in another package in the 
 FT-100D.
 
 Output D11 thru a 1st order LPF (10K ohm resistor, 10uf cap) will 
 give you the CI-V values for the Xiegu XPA125B amp.  Double check the 
 voltages before you connect it to your amp as this is untested beyond
 using a DVM to measure the voltages.
 
 Input D12 is the TTL level input from the Hermes Lite 2.0's DB9 connector.
 An external pullup resistor is not needed, it's provided by the Arduino Nano.
 
