req = [0, 30, 41, 62, 14]
head = 20

print("FCFS Disk Scheduling")
total = 0
current = head

for r in req:
    total = total + abs(current - r)
    current = r

print("Order:", req)
print("Total Seek Time:", total)
print("\nSSTF Disk Scheduling")

req2 = [0, 30, 41, 62, 14]
current = head
total = 0
order = []

while len(req2) > 0:
    near = req2[0]

    for r in req2:
        if abs(current - r) < abs(current - near):
            near = r

    total = total + abs(current - near)
    order.append(near)
    current = near
    req2.remove(near)

print("Order:", order)
print("Total Seek Time:", total)
print("\nSSTF is better than FCFS")