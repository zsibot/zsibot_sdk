import os
import platform
import sys
import time

# Setup library path
arch = platform.machine().replace('amd64', 'x86_64').replace('arm64', 'aarch64')
lib_path = os.path.abspath(
    f'{os.path.dirname(__file__)}/../../../../lib/zsl-1/{arch}')
sys.path.insert(0, lib_path)

import mc_sdk_zsl_1_py

def print_menu():
    """Prints the interactive command menu."""
    print("\nZsiBot Interactive Demo")
    print("-----------------------")
    print("1. Stand Up")
    print("2. Lie Down")
    print("3. Move Forward")
    print("4. Move Backward")
    print("5. Move Left")
    print("6. Move Right")
    print("7. Turn Left")
    print("8. Turn Right")
    print("9. Jump")
    print("10. Front Jump")
    print("11. Backflip")
    print("12. Shake Hand")
    print("13. Attitude Control (Gentle Wobble)")
    print("0. Exit")
    print("-----------------------")


def main():
    """Main function to run the interactive demo."""
    try:
        app = mc_sdk_zsl_1_py.HighLevel()
        # Use 127.0.0.1 for both local and robot IP for simulation/local testing
        app.initRobot("127.0.0.1", 43988, "127.0.0.1")
        print("Successfully initialized robot connection.")

        # It's often necessary to stand up first
        print("Robot is standing up...")
        app.standUp()
        time.sleep(3)
        print("Robot is ready for commands.")

        while True:
            print_menu()
            choice = input("Enter command number: ")

            if choice == '1':
                print("Executing: Stand Up")
                app.standUp()
                time.sleep(3)
            elif choice == '2':
                print("Executing: Lie Down")
                app.lieDown()
                time.sleep(3)
            elif choice == '3':
                print("Executing: Move Forward (for 2s)")
                app.move(0.2, 0, 0)
                time.sleep(2)
                app.move(0, 0, 0)  # Stop
            elif choice == '4':
                print("Executing: Move Backward (for 2s)")
                app.move(-0.2, 0, 0)
                time.sleep(2)
                app.move(0, 0, 0)  # Stop
            elif choice == '5':
                print("Executing: Move Left (for 2s)")
                app.move(0, 0.2, 0)
                time.sleep(2)
                app.move(0, 0, 0)  # Stop
            elif choice == '6':
                print("Executing: Move Right (for 2s)")
                app.move(0, -0.2, 0)
                time.sleep(2)
                app.move(0, 0, 0)  # Stop
            elif choice == '7':
                print("Executing: Turn Left (for 2s)")
                app.move(0, 0, 0.3)
                time.sleep(2)
                app.move(0, 0, 0)  # Stop
            elif choice == '8':
                print("Executing: Turn Right (for 2s)")
                app.move(0, 0, -0.3)
                time.sleep(2)
                app.move(0, 0, 0)  # Stop
            elif choice == '9':
                print("Executing: Jump")
                app.jump()
                time.sleep(4)
            elif choice == '10':
                print("Executing: Front Jump")
                app.frontJump()
                time.sleep(4)
            elif choice == '11':
                print("Executing: Backflip")
                app.backflip()
                time.sleep(4)
            elif choice == '12':
                print("Executing: Shake Hand")
                app.shakeHand()
                time.sleep(4)
            elif choice == '13':
                print("Executing: Attitude Control (for 4s)")
                app.attitudeControl(0.1, 0.1, 0.1, 0.1)
                time.sleep(4)
                app.standUp()  # Return to a stable state
                time.sleep(2)
            elif choice == '0':
                print("Exiting demo. Robot will lie down.")
                app.lieDown()
                time.sleep(3)
                break
            else:
                print("Invalid choice. Please try again.")

            # Ensure robot is in a stable standing state after most actions
            if choice not in ['1', '2', '0']:
                app.standUp()
                time.sleep(2)

    except ImportError:
        print("Error: The 'mc_sdk_zsl_1_py' module could not be found.")
        print(
            f"Please ensure the library for your architecture ('{arch}') is in the path: {lib_path}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")


if __name__ == "__main__":
    main()
