#include <obs-module.h>
#include <util/platform.h>
#include <string>
#include <vector>

// Структура для хранения информации о паре участников
struct ParticipantPair {
    std::string name1;
    std::string name2;
    std::string status;
};

// Глобальные данные плагина
struct competition_overlay_data {
    obs_source_t *source;
    ParticipantPair pair1;
    ParticipantPair pair2;
};

// Функция рендеринга текста на экране
static void render(void *data, gs_effect_t *effect) {
    struct competition_overlay_data *overlay = (struct competition_overlay_data *)data;

    // Текст для отображения
    std::string text1 = overlay->pair1.name1 + " / " + overlay->pair1.name2 + " | " + overlay->pair1.status;
    std::string text2 = overlay->pair2.name1 + " / " + overlay->pair2.name2 + " | " + overlay->pair2.status;

    // Используем стандартный шрифт OBS
    obs_source_draw_text("Arial", text1.c_str(), 0xFFFFFF, 0, 0);
    obs_source_draw_text("Arial", text2.c_str(), 0xFFFFFF, 0, 30);
}

// Функция создания источника
static void *create(obs_data_t *settings, obs_source_t *source) {
    struct competition_overlay_data *overlay = (struct competition_overlay_data *)bzalloc(sizeof(*overlay));
    overlay->source = source;

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
    bfree(overlay);
}

// Описание свойств источника
static obs_properties_t *get_properties(void *data) {
    obs_properties_t *props = obs_properties_create();

    obs_property_t *p1_name1 = obs_properties_add_text(props, "pair1_name1", "Имя 1-го участника пары 1", OBS_TEXT_DEFAULT);
    obs_property_t *p1_name2 = obs_properties_add_text(props, "pair1_name2", "Имя 2-го участника пары 1", OBS_TEXT_DEFAULT);
    obs_property_t *p1_status = obs_properties_add_text(props, "pair1_status", "Статус пары 1", OBS_TEXT_DEFAULT);

    obs_property_t *p2_name1 = obs_properties_add_text(props, "pair2_name1", "Имя 1-го участника пары 2", OBS_TEXT_DEFAULT);
    obs_property_t *p2_name2 = obs_properties_add_text(props, "pair2_name2", "Имя 2-го участника пары 2", OBS_TEXT_DEFAULT);
    obs_property_t *p2_status = obs_properties_add_text(props, "pair2_status", "Статус пары 2", OBS_TEXT_DEFAULT);

    return props;
}

// Обновление параметров источника
static void update(void *data, obs_data_t *settings) {
    struct competition_overlay_data *overlay = (struct competition_overlay_data *)data;

    overlay->pair1.name1 = obs_data_get_string(settings, "pair1_name1");
    overlay->pair1.name2 = obs_data_get_string(settings, "pair1_name2");
    overlay->pair1.status = obs_data_get_string(settings, "pair1_status");

    overlay->pair2.name1 = obs_data_get_string(settings, "pair2_name1");
    overlay->pair2.name2 = obs_data_get_string(settings, "pair2_name2");
    overlay->pair2.status = obs_data_get_string(settings, "pair2_status");
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
extern "C" __declspec(dllexport) void obs_module_load(void) {
    obs_register_source(&competition_overlay);
}