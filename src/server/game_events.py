import struct


GAME_EVENT_MAX_SIZE = 0x4 + 0x4 + 0x1400

EXCLUDED_GAME_EVENT_TYPES = [
    0x27,
    0x35,
    0x46,
    0x48,
    0x4B,
    0x4C,
    0x4D,
    0x52,
    0x54,
    0x57,
    0x58,
    0x5A,
    0x83,
    0x87,
    0x89,
    0x8A,
]


def print_game_event(game_event_type: int, game_event_size: int, game_event_data: bytes) -> None:
    if game_event_type in EXCLUDED_GAME_EVENT_TYPES:
        return

    print(f"{game_event_type :2X}  {game_event_size :4X}  {game_event_data.hex(' ').upper()}")


def process_game_event(data: bytes) -> None:
    game_event_type = struct.unpack("<l", data[0x0:0x4])[0]
    game_event_size = struct.unpack("<L", data[0x4:0x8])[0]
    game_event_data = data[0x8:0x8+game_event_size]
    
    print_game_event(game_event_type, game_event_size, game_event_data)