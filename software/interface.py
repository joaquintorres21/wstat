import dearpygui.dearpygui as dpg
from screeninfo import get_monitors

DHT22 = 0  
MQ135 = 1

SCR_DIM = get_monitors()[0]
SCR_WIDTH = SCR_DIM.width
SCR_HEIGHT = SCR_DIM.height

def toggle_sensor(sensor_id: int):
    pass

def is_sensor_on(sensor_id: int):
    pass

def build_settings():
    dpg.add_button(label="Toggle DHT22", parent="OptWin", callback=lambda: toggle_sensor(DHT22))
    dpg.add_button(label="Toggle MQ135", parent="OptWin", callback=lambda: toggle_sensor(MQ135))


def build_temp(data: list[int]):
    dpg.add_plot(label="Temperatura", parent="DHT")
    dpg.add_plot(label="Humedad", parent="DHT")

def build_co2(data: int):
    dpg.add_plot(label="CO_2 en el aire", parent="MQ")
    
def build_pressure(data: int):
    dpg.add_Plot(label="")

def start():
    dpg.create_context()
    with dpg.window(tag="MainWin",label="wstatViewer",):
        pass
    with dpg.group(tag="DHT", parent="MainWin", horizontal=True):
        pass
    with dpg.group(tag="MQ", parent="MainWin", horizontal=True):
        pass
    dpg.add_window
    with dpg.window(tag="OptWin",label="Settings", pos=[SCR_WIDTH*0.75,10], width=0.2*SCR_WIDTH, height=0.1*SCR_HEIGHT, no_move= True, no_close=True, no_resize=True):
        pass
    dpg.create_viewport(title='wstatViewer', clear_color=(50,50,50,0), width=SCR_WIDTH-10, height=SCR_HEIGHT-10)
    dpg.setup_dearpygui()
    dpg.toggle_viewport_fullscreen()
    dpg.show_viewport()
    return dpg.set_primary_window("MainWin", True)

def run(data_from_micro):
    start()
    build_temp({1,2})
    build_co2({1,1})
    build_settings()
    while dpg.is_dearpygui_running():
        dpg.render_dearpygui_frame()
    
    dpg.destroy_context()


#testing with dearpygui
if __name__ == '__main__':
    run(0)