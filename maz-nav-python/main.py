import bluetooth

print("Searching for bluetooth devices")
devices = bluetooth.discover_devices(lookup_names=True)

for addr, name in devices:
    print("{0} - {1}".format(addr, name))
