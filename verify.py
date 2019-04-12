import os

for ipc in ["pipes", "sockets", "message-passing", "shared"]:
    consumer = "%s/consumer.txt" % ipc
    producer = "%s/producer.txt" % ipc
    if not (os.path.exists(consumer) and os.path.exists(producer)):
        continue

    for line, line_pair in enumerate(zip(open(consumer).readlines(), open(producer).readlines())):
        if line_pair[0] != line_pair[1]:
            print("rows %d are not the same" % line)
            break
            
    print("output for %s is corret" % ipc)