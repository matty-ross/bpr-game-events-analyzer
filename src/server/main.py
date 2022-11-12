import threading

import server


SERVER_IP = "127.0.0.1"
PORT = 7777


def main() -> None:
    game_events_server = server.Server()
    game_events_server_thread = threading.Thread(target=server.Server.start, args=[game_events_server, SERVER_IP, PORT])
    game_events_server_thread.start()

    game_events_server_thread.join()


if __name__ == "__main__":
    main()