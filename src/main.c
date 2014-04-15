#include <pebble.h>

Window *my_window;
static Layer *window_layer;
static TextLayer *text_layer;
char minbuffer[] = "00";
static InverterLayer *inv_layer;
static BitmapLayer *background_layer;
static GBitmap *background_image;
static GRect window_bounds;
// Initialize the bounds of the inverse layer
int inv_top;
int inv_bot;
static GRect inv_bounds;

void update_time_min( struct tm* t) {
  //Update the watchface minutes display every minute
  strftime(minbuffer, sizeof("00"), "%M", t);
  text_layer_set_text(text_layer, minbuffer);
  int hours = t->tm_hour;
  int minutes = t->tm_min;
  if (hours <= 12) {
    inv_top = 168 - (hours * 14);
    if (minutes > 0 && minutes < 7) {
      inv_top = inv_top - 1;
    }
    if (minutes >= 7 && minutes < 11) {
      inv_top = inv_top - 2;
    }
    if (minutes >= 11 && minutes < 17) {
      inv_top = inv_top - 3;
    }
    if (minutes >= 17 && minutes < 23) {
      inv_top = inv_top - 4;
    }
    if (minutes >= 23 && minutes < 29) {
      inv_top = inv_top - 5;
    }
    if (minutes >= 29 && minutes < 35) {
      inv_top = inv_top - 6;
    }
    if (minutes >= 35 && minutes < 41) {
      inv_top = inv_top - 7;
    }
    if (minutes >= 41 && minutes < 47) {
      inv_top = inv_top - 8;
    }
    if (minutes >= 47 && minutes < 53) {
      inv_top = inv_top - 9;
    } 
    if (minutes >= 53 && minutes < 59) {
      inv_top = inv_top - 10;
    }
    inv_bot = 168 - inv_top;
  } else {
    inv_top = 0;
    inv_bot = 168 - ((hours - 12) * 14);
    if (minutes > 0 && minutes < 7) {
      inv_bot = inv_bot - 1;
    }
    if (minutes >= 7 && minutes < 11) {
      inv_bot = inv_bot - 2;
    }
    if (minutes >= 11 && minutes < 17) {
      inv_bot = inv_bot - 3;
    }
    if (minutes >= 17 && minutes < 23) {
      inv_bot = inv_bot - 4;
    }
    if (minutes >= 23 && minutes < 29) {
      inv_bot = inv_bot - 5;
    }
    if (minutes >= 29 && minutes < 35) {
      inv_bot = inv_bot - 6;
    }
    if (minutes >= 35 && minutes < 41) {
      inv_bot = inv_bot - 7;
    }
    if (minutes >= 41 && minutes < 47) {
      inv_bot = inv_bot - 8;
    }
    if (minutes >= 47 && minutes < 53) {
      inv_bot = inv_bot - 9;
    } 
    if (minutes >= 53 && minutes < 59) {
      inv_bot = inv_bot - 10;
    }
  }
  inverter_layer_destroy(inv_layer);
  inv_bounds = GRect (0, inv_top, 144, inv_bot);
  inv_layer = inverter_layer_create(inv_bounds);
  layer_add_child(window_layer, (Layer*) inv_layer);
}

void set_inv_layer(int hours, int minutes) {
  if (hours <= 12) {
    inv_top = 168 - (hours * 14);
    if (minutes > 0 && minutes < 7) {
      inv_top = inv_top - 1;
    }
    if (minutes >= 7 && minutes < 11) {
      inv_top = inv_top - 2;
    }
    if (minutes >= 11 && minutes < 17) {
      inv_top = inv_top - 3;
    }
    if (minutes >= 17 && minutes < 23) {
      inv_top = inv_top - 4;
    }
    if (minutes >= 23 && minutes < 29) {
      inv_top = inv_top - 5;
    }
    if (minutes >= 29 && minutes < 35) {
      inv_top = inv_top - 6;
    }
    if (minutes >= 35 && minutes < 41) {
      inv_top = inv_top - 7;
    }
    if (minutes >= 41 && minutes < 47) {
      inv_top = inv_top - 8;
    }
    if (minutes >= 47 && minutes < 53) {
      inv_top = inv_top - 9;
    } 
    if (minutes >= 53 && minutes < 59) {
      inv_top = inv_top - 10;
    }
    inv_bot = 168 - inv_top;
  } else {
    inv_top = 0;
    inv_bot = 168 - ((hours - 12) * 14);
    if (minutes > 0 && minutes < 7) {
      inv_bot = inv_bot - 1;
    }
    if (minutes >= 7 && minutes < 11) {
      inv_bot = inv_bot - 2;
    }
    if (minutes >= 11 && minutes < 17) {
      inv_bot = inv_bot - 3;
    }
    if (minutes >= 17 && minutes < 23) {
      inv_bot = inv_bot - 4;
    }
    if (minutes >= 23 && minutes < 29) {
      inv_bot = inv_bot - 5;
    }
    if (minutes >= 29 && minutes < 35) {
      inv_bot = inv_bot - 6;
    }
    if (minutes >= 35 && minutes < 41) {
      inv_bot = inv_bot - 7;
    }
    if (minutes >= 41 && minutes < 47) {
      inv_bot = inv_bot - 8;
    }
    if (minutes >= 47 && minutes < 53) {
      inv_bot = inv_bot - 9;
    } 
    if (minutes >= 53 && minutes < 59) {
      inv_bot = inv_bot - 10;
    }
  }
  //Set up inv_layer
  inv_bounds = GRect (0, inv_top, 144, inv_bot);  
  inv_layer = inverter_layer_create(inv_bounds);
  layer_add_child(window_layer, (Layer*) inv_layer);
}

void update_time( struct tm* t) {
  //Update the watchface minutes display every minute
  strftime(minbuffer, sizeof("00"), "%M", t);
  text_layer_set_text(text_layer, minbuffer);
  set_inv_layer(t->tm_hour, t->tm_min);
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time_min(tick_time);
}

void init(void) {
    //Creates and configures the window layer
    my_window = window_create();
    window_stack_push(my_window, true);
    window_layer = window_get_root_layer(my_window);
    window_bounds = layer_get_bounds(window_layer);
    //Set up the background image
    background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);
    background_layer = bitmap_layer_create(window_bounds);
    layer_add_child(window_layer, bitmap_layer_get_layer(background_layer));
    bitmap_layer_set_bitmap(background_layer, background_image);
    //Set up and display text layer
    text_layer = text_layer_create(GRect (72, 113, 144, 168));
    text_layer_set_background_color(text_layer, GColorClear);
    text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
    text_layer_set_text_color(text_layer, GColorWhite);
    layer_add_child(window_layer, (Layer*) text_layer);
    //Get a time structure so that the face doesn't start blank 
    time_t temp = time(NULL);
    struct tm *t = localtime(&temp);
    update_time(t);
    //Listens for event every minute and runs tick_handler
    tick_timer_service_subscribe(MINUTE_UNIT, &tick_handler);
}

void deinit(void) {
	  window_destroy(my_window);
    text_layer_destroy(text_layer);
    bitmap_layer_destroy(background_layer);
    inverter_layer_destroy(inv_layer);
    tick_timer_service_unsubscribe();
}

int main(void) {
	  init();
	  app_event_loop();
	  deinit();
}

