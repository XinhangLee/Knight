//
// Created by lixh1 on 25-2-11.
//
#include <Stash.h>

s_bullets init_bullets(const std::string& type) {
    s_bullets b;
    using json = nlohmann::json;
    try {
        std::ifstream file("../rsc/stash/bullet.json");
        if (!file.is_open()) {
            std::cerr << "Failed to open file" << std::endl;
            exit(1);
        }
        json j;
        file >> j;
        if (j.contains(type)) {
            // 从 JSON 中提取子弹数据
            b.attack_power = j[type]["attack_power"];
            b.energy_consumed = j[type]["energy_consumed"];
            b.time_gap = j[type]["time_gap"];
            b.center_bullet.x = j[type]["center_bullet"]["x"];
            b.center_bullet.y = j[type]["center_bullet"]["y"];
            b.speed_bullet = j[type]["speed_bullet"];
            b.frame_num = j[type]["frame_num"];
            b.path = j[type]["path"];
        } else {
            std::cerr << "Bullet type " << type << " not found in JSON file" << std::endl;
            exit(EXIT_FAILURE);
        }
    } catch (json::parse_error& ex) {
        std::cerr << "JSON parse error: " << ex.what() << std::endl;
        exit(1);
    } catch (json::out_of_range& ex) {
        std::cerr << "JSON out of range error: " << ex.what() << std::endl;
        exit(1);
    } catch (std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(1);
    }
    return b;
}
s_weapons init_weapons(const std::string& type) {
    s_weapons w;
    using json = nlohmann::json;
    try {
        std::ifstream file("../rsc/stash/weapon.json");
        if (!file.is_open()) {
            std::cerr << "Failed to open file" << std::endl;
            exit(1);
        }
        json j;
        file >> j;
        if (j.contains(type)) {
            // 从 JSON 中提取武器数据
            w.center_weapon.x = j[type]["center_weapon"]["x"];
            w.center_weapon.y = j[type]["center_weapon"]["y"];
            w.launch_point.x = j[type]["launch_point"]["x"];
            w.launch_point.y = j[type]["launch_point"]["y"];
            w.path = j[type]["path"];

            // 初始化 bullet_type
            const std::string bullet_type_name = j[type]["bullet_type"];
            w.bullet_type = init_bullets(bullet_type_name);
        } else {
            std::cerr << "Weapon type " << type << " not found in JSON file" << std::endl;
            exit(EXIT_FAILURE);
        }
    } catch (json::parse_error& ex) {
        std::cerr << "JSON parse error: " << ex.what() << std::endl;
        exit(1);
    } catch (json::out_of_range& ex) {
        std::cerr << "JSON out of range error: " << ex.what() << std::endl;
        exit(1);
    } catch (std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(1);
    }
    return w;
}
s_heroes init_heroes(const std::string& type) {
    s_heroes h;
    using json = nlohmann::json;
    try {
        std::ifstream file("../rsc/stash/hero.json");
        if (!file.is_open()) {
            std::cerr << "Failed to open file" << std::endl;
            exit(1);
        }
        json j;
        file >> j;
        if (j.contains(type)) {
            // 从 JSON 中提取英雄数据
            h.HP[0] = j[type]["HP"][0];
            h.HP[1] = j[type]["HP"][1];
            h.shield[0] = j[type]["shield"][0];
            h.shield[1] = j[type]["shield"][1];
            h.energy[0] = j[type]["energy"][0];
            h.energy[1] = j[type]["energy"][1];
            h.speed = j[type]["speed"];
            h.pos_hero.x = j[type]["pos_hero"]["x"];
            h.pos_hero.y = j[type]["pos_hero"]["y"];
            h.center_hero.x = j[type]["center_hero"]["x"];
            h.center_hero.y = j[type]["center_hero"]["y"];
            h.weapon_point.x = j[type]["weapon_point"]["x"];
            h.weapon_point.y = j[type]["weapon_point"]["y"];
            h.frame_num = j[type]["frame_num"];
            h.StablePath = j[type]["StablePath"];
            h.WalkPath = j[type]["WalkPath"];
            const std::string weapon_type_name = j[type]["weapon_type"];
            h.weapon_type = init_weapons(weapon_type_name);
        } else {
            std::cerr << "Hero type " << type << " not found in JSON file" << std::endl;
            exit(EXIT_FAILURE);
        }
    } catch (json::parse_error& ex) {
        std::cerr << "JSON parse error: " << ex.what() << std::endl;
        exit(1);
    } catch (json::out_of_range& ex) {
        std::cerr << "JSON out of range error: " << ex.what() << std::endl;
        exit(1);
    } catch (std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(1);
    }
    return h;
}
s_monsters init_monsters(const std::string& type) {
    s_monsters m;
    using json = nlohmann::json;
    try {
        std::ifstream file("../rsc/stash/monster.json");
        if (!file.is_open()) {
            std::cerr << "Failed to open file" << std::endl;
            exit(1);
        }
        json j;
        file >> j;
        if (j.contains(type)) {
            m.HP = j[type]["HP"];
            m.range = j[type]["range"];
            m.speed_monster = j[type]["speed_monster"];
            m.center_monster.x = j[type]["center_monster"]["x"];
            m.center_monster.y = j[type]["center_monster"]["y"];
        }else {
            std::cerr << "Monster type " << type << " not found in JSON file" << std::endl;
            exit(EXIT_FAILURE);
        }
    } catch (json::parse_error& ex) {
        std::cerr << "JSON parse error: " << ex.what() << std::endl;
        exit(1);
    } catch (json::out_of_range& ex) {
        std::cerr << "JSON out of range error: " << ex.what() << std::endl;
        exit(1);
    } catch (std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        exit(1);
    }
    return m;
}
int walls_1[4][4] = {
    {307, 60, 61, 880},//left
    {307, 60, 885, 62},//up
    {1132, 60, 61, 880},//right
    {307, 880, 885, 60}//down
};