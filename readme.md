# Corne Japanese Duplex keyboard
## Image to Code C++
https://javl.github.io/image2cpp/

## Font edit
https://joric.github.io/qle/

![Scheme](/assets/scheme.png)
![Scheme1](/assets/scheme1.png)
![Scheme2](/assets/scheme2.png)


        {
            "label": "Custom",
            "content": [
                {
                    "label": "Oled",
                    "content": [
                        {
                            "label": "Master Oled",
                            "type": "dropdown",
                            "options": [
                              ["Bongo-cat", 0],
                              ["Info", 1],
                              ["Image1", 2],
                              ["Image2", 3],
                              ["Image3", 4],
                              ["Tic Tac Toe", 5],
                              ["Snake", 6],
                              ["Calculator", 7],
                              ["Arasaka (reboot keyboard)", 8],
                              ["SS", 9]
                            ],
                            "content": ["id_master_animation", 0, 0]
                          },
                        {
                            "label": "Slave Oled",
                            "type": "dropdown",
                            "options": [
                              ["Bongo-cat", 0],
                              ["Info", 1],
                              ["Image1", 2],
                              ["Image2", 3],
                              ["Image3", 4],
                              ["Tic Tac Toe", 5],
                              ["Snake", 6],
                              ["Calculator", 7],
                              ["Arasaka (reboot keyboard)", 8],
                              ["SS", 9]
                            ],
                            "content": ["id_slave_animation", 0, 1]
                          }
                    ]
                }
            ]
        }
    