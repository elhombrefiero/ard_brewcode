# ard_brewcode
Arduino Brew Code. Reads temperatures using OneWire temperature sensors and modifies heater and pumps based on input setpoints.

Recommended to use an Arduino Mega for memory purposes.

Requires the ArduinoJSON, ArduinoSTL packages.

API:
Communication to/from the brewcode will be via the serial in json format. Note that there is a 64-byte limit on what can be sent through serial at a time.

Overall commands: 
    {type:general, auto: on[off]} - When on (default), the code will automatically control heaters/pumps using the sensor information. Setting this to off will leave the controllers in their previous state and will rely on manual commands to control switch positions.
    
    The users can specify zero to many heaters for use in the system. Beware of memory limitations!!!
    {type:heater, add_heater:true} - Adds one heater to the current run.

Heater-specific commands:
    NOTE: Every heater command requires type:heater and one of the following: name:<name_of_heater> or index:<index_of_heater> in the JSON command. Examples below:
    
    {type:heater, index:<index_of_heater>, …}, {type:heater, name:<name_of_heater>, ..} 
    
    The default heater name is "Heater" 
    
    If a user overrides the heater name, he/she must update any JSON command(s) to reflect that. Name is also case-sensitive.
    
    The remaining command definitions will only show the index:<index_of_heater> for brevity.
    
    Also, note that multiple heater commands can be issued at once. The JSON command line fits 256 characters.
    
    {type:heater, index:<index_of_heater>, new_name:<new_name_of_heater>} - Updates the heater name.
    
    {type:heater, index:<index_of_heater>, setpoint_high:<new_setpoint_high_val>} - Updates the heater setpoint_high value.
    
    {type:heater, index:<index_of_heater>, setpoint_low:<new_setpoint_low_val>} - Updates the heater setpoint_lowvalue.
    
    {type:heater, index:<index_of_heater>, setpoint_max:<new_setpoint_max_val>} - Updates the heater setpoint_max value.
    
    {type:heater, index:<index_of_heater>, pin:<new_pin> - Updates the heater to use new_pin as the pin to control.
    
    {type:heater, index:<index_of_heater>, status:<true/false>} - Controls whether the heater is on or off.
    
    {type:heater, index:<index_of_heater>, tsensor_address:<new_tsensor_address>} - Assigns the tsensor at the address "new_tsensor_address" to compare against when controlling the heater. Multiple tsensors can be added if desired.
    
    {type:heater, index:<index_of_heater>, remove_tsensors:true} - Removes all associated temperature sensors from heater <index>.	
