"""
    Author: Dante Trisciuzzi
    Purpose: Project 2 for IT-140-X2959
    Date: 12.5.2021
"""

import random
import time

# secret painting for the good ending
painting = \
        R"    .-.                                    ,-.       " + "\n" \
        R"  .-(   )-.                              ,-(   )-.   " + "\n" \
        R" (     __) )-.                        ,-(_      __)  " + "\n" \
        R"  `-(       __)                      (_    )  __)-'  " + "\n" \
        R"    `(____)-',                        `-(____)-'     " + "\n" \
        R"  - -  :   :  - -                                    " + "\n" \
        R"      / `-' \                                        " + "\n" \
        R"    ,    |   .                                       " + "\n" \
        R"         .                         _                 " + "\n" \
        R"                                  >')                " + "\n" \
        R"               _   /              (\\         (W)    " + "\n" \
        R"              =') //               = \     -. `|'    " + "\n" \
        R"               ))////)             = ,-      \(| ,-  " + "\n" \
        R"              ( (///))           ( |/  _______\|/____" + "\n" \
        R"~~~~~~~~~~~~~~~`~~~~'~~~~~~~~~~~~~\|,-'::::::::::::::" + "\n" \
        R"            _                 ,----':::::::::::::::::" + "\n" \
        R"         {><_'c   _      _.--':::::::::::::::::::::::" + "\n" \
        R"_,'`----._,-. {><_'c  _-'::::::::::::::::::::::::::: " + "\n" \
        R":.:.:.:.:.:.:.\_    ,-'.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:" + "\n" \
        R".:.:.:.:.:.:.:.:`--'.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:." + "\n" \
        R"....................................................." + "\n"

start_location = 'Atrium'
items_to_win = 8

endgame_header = "There it is, it's just a canvas....right? Seems perfectly normal.." \
                 "\n...You approach the canvas..."

bad_ending_text = endgame_header + \
                  "\nSuddenly, you feel cold... frozen... you're stuck." \
                  "\nThe walls are closing in..." \
                  "\nNothing is left." \
                  "\nGAME OVER"

good_ending_text = endgame_header + \
                   "\nIt's noticeably cold, but you lay out your equipment and get started." \
                   "\nAfter the first cloud in Titanium White is laid on the canvas, the room seems.. bigger" \
                   "\nYou paint the perfect picture, and saved the world." \
                   "\nYOU WIN"

rooms = {
    'Atrium': {'east': 'Kitchen', 'west': 'Study (West wing)', 'north': 'Dining Room'},
    'Kitchen': {'west': 'Atrium', 'north': 'Den'},
    'Study (West wing)': {'north': 'Bedroom', 'east': 'Atrium'},
    'Dining Room': {'south': 'Atrium'},
    'Bedroom': {'north': 'Sun Room', 'south': 'Study (West wing)', 'east': 'Cellar'},
    'Den': {'north': 'Study (East wing)', 'south': 'Kitchen'},
    'Sun Room': {'south': 'Bedroom', 'east': 'Garage'},
    'Garage': {'south': 'Cellar', 'east': 'Study (East wing)', 'west': 'Sun Room'},
    'Study (East wing)': {'south': 'Den', 'west': 'Garage'},
    'Cellar': {'villain': True, 'north': 'Garage', 'west': 'Bedroom'},
}

available_items = {
    'tool': ["Two-inch brush", "Palette knife"],
    'paint': ["Alizarin Crimson", "Cadmium Yellow", "Prussian Blue",
              "Phthalo Green", "Titanium White", "Van Dyke Brown"]
}

player_inventory = {
    'tool': [],
    'paint': []
}

# valid commands with valid parameters
valid_commands = {
    # I will use all lowercase commands, and use input().lower() to ensure consistency.
    'go': ['north', 'south', 'east', 'west'],
    'exit': ['exit'],
    'get': ['tool', 'paint']
}


def print_slow(text: str, interval: int) -> None:
    """
    Prints a message line by line with an interval between lines
    :param text: Text to print
    :param interval: interval between lines
    :return: None
    """
    for line in text.split('\n'):
        time.sleep(interval)
        print(line)


def print_inventory() -> None:
    """
    Prints player inventory broken into categories
    :returns: None
    """
    print("Inventory:")
    for k, v in player_inventory.items():
        print(f"\t{k.capitalize()}s:{'' if len(v) > 0 else 'empty'}", end='')
        for i in enumerate(v):
            print(f" {i[1]}{',' if i[0] < len(v) - 1 else ''}", end='')
        print()


def place_items():
    """
    Shuffles items and assigns them to every room besides starting and villain rooms.
    :returns: None
    """
    items_list = available_items['tool'] + available_items['paint']
    random.shuffle(items_list)

    for room in rooms.items():
        if room[0] == start_location or room[1].keys().__contains__('villain'):
            continue

        if not room[1].keys().__contains__('item'):
            if items_list.__len__() > 0:
                room[1]['item'] = items_list.pop(0)


def get_item_type(item: str) -> str:
    """
    Returns the type of an item if exists in available_items{}
    :param item: the item of unknown type
    :return: the item's type
    """
    if item in available_items['paint']:
        return 'paint'
    elif item in available_items['tool']:
        return 'tool'
    return 'ERROR: Invalid Item'


def try_add_item(room: str, requested_item_type: str) -> bool:
    """
    Tries to add item to player inventory from current room
    :param room: the current room to check
    :param requested_item_type: the item type specified by the player
    :return: if the item is added to the player inventory
    """
    if room == start_location or rooms[room].keys().__contains__('villain'):
        print("Can't get item in villain room!")
        return False

    if not rooms[room].keys().__contains__('item'):
        print("There is no item in this room!")
        return False

    this_item = rooms[room]['item']
    if get_item_type(this_item) != requested_item_type:
        print(f"There is no {requested_item_type} in this room!")
        return False

    player_inventory[get_item_type(this_item)].append(this_item)
    del rooms[room]['item']
    return True


def show_item_in_room(room: str) -> None:
    """
    Prints item in room or no item message
    :param room: the current room to check
    :returns: None
    """
    if rooms[room].keys().__contains__('villain'):
        return

    if not rooms[room].keys().__contains__('item') or room == start_location:
        print("There is no items in this room.")
        return

    this_item = rooms[room]['item']
    print(f"You see your {'tube of ' if get_item_type(this_item) == 'paint' else ''}{this_item}.")


def show_commands() -> None:
    """
    Prints commands to console
    :return: None
    """
    print("Move by typing \'go\' (without quotes) and the direction you want to move.")
    print("Collect an item with \'get\' (without quotes) and the item type (paint or tool).")
    print("You may also exit the game by typing \'exit\' (without quotes).")
    print("Valid commands: ", end='')
    for direction in valid_commands['go']:
        print('go ' + direction, end=', ')
    print('get paint, get tool, exit.')


def parse_input(raw_command: list) -> (str, str):
    """
    Takes Raw user input and determines commands
    :param raw_command: list of str
    :return: command, parameter if valid else None,None
    """
    if raw_command[0] in valid_commands.keys():
        parameter = raw_command[1 if raw_command.__len__() > 1 else 0]
        if parameter in valid_commands[raw_command[0]]:
            # Only set command and parameter is valid
            return raw_command[0], parameter
        print(F"You cannot use the command \'{raw_command[0]}\' with the parameter \'{parameter}\', please try again!")
        return None, None
    print(F"The command \'{raw_command[0]}\' is not recognized.")
    return None, None


def process_command(cmd: str, param: str, room: str) -> str:
    """
    Takes parsed command and parameter from parse_input() and performs actions
    :param cmd: Command
    :param param: Parameter for Command
    :param room: Current room for lookup
    :return: new room if direction is valid else old room
    """
    if cmd is not None and param is not None:
        if cmd == 'exit':
            return 'exit'
        if cmd == 'get':
            try_add_item(room, param)
            return room
        if param in rooms[room]:
            print(F"You go {param}.")
            return rooms[room][param]
        print("You can't go that way!")
        return room
    return room


def check_villain_room(room: str) -> bool:
    """
    Checks if this room contains the villain
    :param room: current room to check
    :return: True if villain in room, False otherwise
    """
    if 'villain' in rooms[room]:
        return True
    return False


def play_end_sequence(text: str) -> None:
    """
    Plays end sequence (steps through lines)
    :param text: the sequence to play
    :return: None
    """
    print_slow(text, 2)

    for i in range(5):
        print('.', end='')
        time.sleep(1)
    print()


def do_villain_fight(room) -> None:
    """
    Makes check for appropriate number of items to win the game, calls appropriate end sequence.
    :param room: current room for display
    :return: None
    """
    print(f"You enter the {room}, and you see the canvas.")
    if not len(player_inventory['paint'] + player_inventory['tool']) >= items_to_win:
        play_end_sequence(bad_ending_text)
        return
    play_end_sequence(good_ending_text)
    print(painting)


if __name__ == '__main__':

    place_items()
    player_name = str(input("Enter your first name: "))
    print_slow("\nWelcome to the ross family mansion.\n"
               f"\nYou, {player_name} Ross, are the descendant of the great landscape artist Bob Ross."
               "An evil canvas is threatening the world, and you are the only one who can stop it!"
               "\nYou must find all your gear before you can paint the evil canvas with the perfect painting to save "
               "the world! "
               "\nYou need to find both of your tools, brush and palette knife, as well as all six unique colors of "
               "paint. "
               f"\nMake haste, {player_name}! The fate of humanity depends on YOU.\n\n", 1)

    show_commands()
    current_room = start_location

    while current_room != 'exit':
        if check_villain_room(current_room):
            do_villain_fight(current_room)
            break

        print('~'*20)
        print(F"\nYou are currently in the {current_room}.")

        print_inventory()
        show_item_in_room(current_room)
        print("Enter your move:")

        parsed_command, parsed_parameter = parse_input(input("> ").lower().split())
        current_room = process_command(parsed_command, parsed_parameter, current_room)

    print("\n\nThank you for playing, see you next time!")
