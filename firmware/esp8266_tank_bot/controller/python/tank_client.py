import sys, requests

def move(host, direction, speed=None):
    params = {"dir": direction}
    if speed is not None:
        params["spd"] = speed
    r = requests.get(f"http://{host}/move", params=params, timeout=3)
    print(r.text)

def main():
    if len(sys.argv) < 3:
        print("Usage: python tank_client.py <host> <fwd|back|left|right|stop> [speed(0-1023)]")
        return
    host = sys.argv[1]
    direction = sys.argv[2]
    speed = int(sys.argv[3]) if len(sys.argv) > 3 else None
    move(host, direction, speed)

if __name__ == "__main__":
    main()
