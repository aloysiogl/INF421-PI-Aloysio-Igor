import sys
import random

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Needs length of the tree")
        exit()
    tot_nodes = int(sys.argv[1])
    to_add_nodes = tot_nodes -1

    curr_node = 1
    last_node = 1

    file = open("new_tree.txt", "w")
    to_write = str(tot_nodes)+"\n"

    for i in range(2, tot_nodes+1):
        to_write += str(random.randint(1, i-1)) + " " + str(i) + "\n"

    for i in range(tot_nodes):
        to_write += str(random.randint(1, 10000))+"\n"

    file.write(to_write)

    file.close()

    print(random.randint(1, 10))