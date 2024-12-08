import serial
import pygame
import time
#import serial.tools.list_ports


# Set the serial port and baud rate
#SERIAL_PORT = "COM6" 
# Replace with your Arduino's port
#BAUD_RATE = 9600

# Initialize Pygame Mixer
pygame.mixer.init()

# Function to play a song
def play_song(file_path):
    pygame.mixer.music.load(file_path)
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy():  # Wait until the music stops
        time.sleep(1)

def main():
    #Open the serial connection
    try:
        ser = serial.Serial("COM6", 9600, timeout=1)
        print(f"Listening on {ser.port}...")
        while True:
            if ser.in_waiting > 0:
                command = ser.readline().decode('utf-8').strip()
                print(command)
                if command == "relaxingMusic\n":
                    print("Trigger received! Playing song...")
                    play_song(r"C:/Users/espad/Desktop/test/1.mp3")  # Replace with the song path
                if command == "melancholicMusic\n":
                    play_song(r"C:/Users/espad/Desktop/test/2.mp3")  # Replace with the song path
                if command == "calmingMusic\n":
                    play_song(r"C:/Users/espad/Desktop/test/3.mp3")  # Replace with the song path
                if command == "productiveMusic\n":
                    play_song(r"C:/Users/espad/Desktop/test/4.mp3")  # Replace with the song path\
                if command == "happyMusic\n":
                    play_song(r"C:/Users/espad/Desktop/test/5.mp3")  # Replace with the song path

                    
    except Exception as e:
        print(f"Error: {e}")
    finally:
        pygame.mixer.quit()
    ##################
    
    # print("MUIE")
    # ports = [port.device for port in serial.tools.list_ports.comports()]
    # print("Available ports:", ports)
    # try:
    #     ser = serial.Serial("COM6", 9600, timeout=1)
    #     print("Connected!")
    #     while True:
    #         if ser.in_waiting > 0:
    #             print(ser.readline().decode('utf-8').strip())
    #         time.sleep(0.1)
    # except Exception as e:
    #     print(f"Error: {e}")

if __name__ == "__main__":
    main()