import dearpygui.dearpygui as dpg
from screeninfo import get_monitors

DHT22 = 0  
MQ135 = 1
BMP280 = 2

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
    dpg.add_button(label="Toggle BMP280", parent="OptWin", callback= lambda: toggle_sensor(BMP280))


def build_temp(data: list[int]):
    temp = dpg.add_plot(label="Temperatura",
                parent="DHT", 
                width=SCR_WIDTH*.2, 
                height=SCR_HEIGHT*.25)
    hum = dpg.add_plot(
        label="Humedad", 
        parent="DHT", 
        width=SCR_WIDTH*.2, 
        height=SCR_HEIGHT*.25)

def build_co2(data: int):
    dpg.add_plot(label="CO_2 en el aire", parent="MQ",width=SCR_WIDTH*.2, height=SCR_HEIGHT*.25)
    
def build_pressure(data: int):
    dpg.add_Plot(label="")

def start():
    dpg.create_context()

    with dpg.theme() as global_theme:

        with dpg.theme_component(dpg.mvAll):
            dpg.add_theme_color(dpg.mvThemeCol_FrameBg, (255, 140, 23), category=dpg.mvThemeCat_Core)
            dpg.add_theme_style(dpg.mvStyleVar_FrameRounding, 5, category=dpg.mvThemeCat_Core)

        with dpg.theme_component(dpg.mvInputInt):
            dpg.add_theme_color(dpg.mvThemeCol_FrameBg, (140, 255, 23), category=dpg.mvThemeCat_Core)
            dpg.add_theme_style(dpg.mvStyleVar_FrameRounding, 5, category=dpg.mvThemeCat_Core)

    with dpg.font_registry():
    # first argument ids the path to the .ttf or .otf file
        title_font = dpg.add_font("C:\\Users\\Joaquin\\Documents\\GitHub\\wstat\\software\\airstrike.ttf", 20)
        
    with dpg.window(tag="MainWin",label="wstatViewer"):
        title = dpg.add_text("wstat Viewer", tag="title", pos=[SCR_WIDTH*0.4, 10])
        dpg.bind_item_font(title, title_font)
        pass
    with dpg.group(tag="DHT", parent="MainWin", horizontal=True,pos=[10,SCR_HEIGHT*0.1]):
        pass
    with dpg.group(tag="MQ", parent="MainWin", horizontal=True,pos=[10,SCR_HEIGHT*0.39]):
        pass
    dpg.add_window
    with dpg.window(tag="OptWin",label="Configuración", pos=[SCR_WIDTH*0.75,SCR_HEIGHT*0.1], width=0.2*SCR_WIDTH, height=0.1*SCR_HEIGHT, no_move= True, no_close=True, no_resize=True):
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