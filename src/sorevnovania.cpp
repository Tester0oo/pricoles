#include <obs-studio/libobs/obs-module.h>
#include <obs-studio/libobs/util/platform.h>
#include <string>
#include <vector>

OBS_DECLARE_MODULE()

// Структура для хранения информации о паре участников
struct ParticipantPair {
    std::string name1;
    std::string name2;
    std::string status;
};

// Глобальные данные плагина
struct competition_overlay_data {
    obs_source_t *source;
    gs_texrender_t *texrender;
    ParticipantPair pair1;
    ParticipantPair pair2;
};

// Функция рендеринга текста на экране
static void render(void *data, gs_effect_t *effect) {
    struct competition_overlay_data *overlay = (struct competition_overlay_data *)data;

    if (!overlay || !effect) return;

    // Текст для отображения
    std::string text1 = overlay->pair1.name1 + " / " + overlay->pair1.name2 + " | " + overlay->pair1.status;
    std::string text2 = overlay->pair2.name1 + " / " + overlay->pair2.name2 + " | " + overlay->pair2.status;

    // Используем texrender для рендеринга
    gs_texrender_reset(overlay->texrender);
    
    // Начинаем рендеринг в текстуру
    if (gs_texrender_begin(overlay->texrender, 1920, 1080)) {
        struct vec4 background;
        vec4_zero(&background);
        gs_clear(GS_CLEAR_COLOR, &background, 0.0f, 0);
        gs_ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -100.0f, 100.0f);

        // Здесь можно добавить рендеринг текста используя obs_source_t
        // или другие графические примитивы
        
        gs_texrender_end(overlay->texrender);
    }

    // Отображаем результирующую текстуру
    gs_texture_t *texture = gs_texrender_get_texture(overlay->texrender);
    if (texture) {
        struct vec2 scale;
        vec2_set(&scale, 1.0f, 1.0f);
        
        gs_effect_set_texture(effect, gs_effect_get_param_by_name(effect, "image"), texture);
        gs_draw_sprite(texture, 0, 0, 0);
    }
}

// Функция создания источника
static void *create(obs_data_t *settings, obs_source_t *source) {
    struct competition_overlay_data *overlay = 
        (struct competition_overlay_data *)bzalloc(sizeof(*overlay));
    overlay->source = source;
    overlay->texrender = gs_texrender_create(GS_RGBA, GS_ZS_NONE);

    // Значения по умолчанию
    overlay->pair1.name1 = "Иванов";
    overlay->pair1.name2 = "Петров";
    overlay->pair1.status = "Ожидание";

    overlay->pair2.name1 = "Сидоров";
    overlay->pair2.name2 = "Козлов";
    overlay->pair2.status = "В работе";

    return overlay;
}

// Функция удаления источника
static void destroy(void *data) {
    struct competition_overlay_data *overlay = (struct competition_overlay_data *)data;
    
    if (overlay) {
        if (overlay->texrender) {
            gs_texrender_destroy(overlay->texrender);
        }
        bfree(overlay);
    }
}

// Описание свойств источника
static obs_properties_t *get_properties(void *data) {
    obs_properties_t *props = obs_properties_create();

    obs_properties_add_text(props, "pair1_name1", "Имя 1-го участника пары 1", OBS_TEXT_DEFAULT);
    obs_properties_add_text(props, "pair1_name2", "Имя 2-го участника пары 1", OBS_TEXT_DEFAULT);
    obs_properties_add_text(props, "pair1_status", "Статус пары 1", OBS_TEXT_DEFAULT);

    obs_properties_add_text(props, "pair2_name1", "Имя 1-го участника пары 2", OBS_TEXT_DEFAULT);
    obs_properties_add_text(props, "pair2_name2", "Имя 2-го участника пары 2", OBS_TEXT_DEFAULT);
    obs_properties_add_text(props, "pair2_status", "Статус пары 2", OBS_TEXT_DEFAULT);

    return props;
}

// Обновление параметров источника
static void update(void *data, obs_data_t *settings) {
    struct competition_overlay_data *overlay = (struct competition_overlay_data *)data;

    if (!overlay || !settings) return;

    const char *str = NULL;
    
    str = obs_data_get_string(settings, "pair1_name1");
    overlay->pair1.name1 = str ? str : "";
    
    str = obs_data_get_string(settings, "pair1_name2");
    overlay->pair1.name2 = str ? str : "";
    
    str = obs_data_get_string(settings, "pair1_status");
    overlay->pair1.status = str ? str : "";

    str = obs_data_get_string(settings, "pair2_name1");
    overlay->pair2.name1 = str ? str : "";
    
    str = obs_data_get_string(settings, "pair2_name2");
    overlay->pair2.name2 = str ? str : "";
    
    str = obs_data_get_string(settings, "pair2_status");
    overlay->pair2.status = str ? str : "";
}

// Описание имени источника
static const char *get_name(void *data) {
    return "Оверлей соревнований";
}

// Определение источника
obs_source_info competition_overlay = {
    .id = "competition_overlay",
    .type = OBS_SOURCE_TYPE_INPUT,
    .output_flags = OBS_SOURCE_VIDEO,
    .get_name = get_name,
    .create = create,
    .destroy = destroy,
    .render = render,
    .update = update,
    .get_properties = get_properties
};

// Регистрация плагина
bool obs_module_load(void) {
    obs_register_source(&competition_overlay);
    return true;
}

void obs_module_unload(void) {
    // Очистка при выгрузке модуля
}
