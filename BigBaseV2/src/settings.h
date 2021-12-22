#pragma once
#include "common.hpp"
#include "gta/player.hpp"

using nlohmann::json;

namespace big
{
	class settings
	{
	public:
		explicit settings() = default;
		~settings() = default;

		const char config[] = "url=http://example.com\n"
			"file=main.exe\n"
			"true=0";


		nlohmann::json options;
		nlohmann::json default_options =
			R"({
				"FaceValue": 0,
				"FaceText": 0,
				"MaskValue": 0,
				"MaskText": 0,
				"HairValue": 0,
				"HairText": 0,
				"TorsoValue": 0,
				"TorsoText": 0,
				"LegValue": 0,
				"LegText": 0,
				"BagValue": 0,
				"BagText": 0,
				"ShoesValue": 0,
				"ShoesText": 0,
				"AccessoryValue": 0,
				"AccessoryText": 0,
				"UndershirtValue": 0,
				"UndershirtText": 0,
				"ArmorValue": 0,
				"ArmorText": 0,
				"DecalsValue": 0,
				"DecalsText": 0,
				"TopsValue": 0,
				"TopsText": 0,
				"HatValue": 0,
				"HatText": 0,
				"GlassValue": 0,
				"GlassText": 0,
				"EarValue": 0,
				"EarText": 0,
				"WatchValue": 0,
				"WatchText": 0,
				"BraceletValue": 0,
				"BraceletText": 0
		})"_json;

		bool save()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += "\\BigBaseV2\\settings.json";

			std::ofstream file(settings_file, std::ios::out | std::ios::trunc);
			file << options.dump(4);
			file.close();
			return true;
		}

		bool load()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += "\\BigBaseV2\\settings.json";

			std::ifstream file(settings_file);

			if (!file.is_open())
			{
				write_default_config();
				file.open(settings_file);
			}

			file >> options;

			bool should_save = false;
			for (auto& e : default_options.items())
			{
				if (options.count(e.key()) == 0)
				{
					should_save = true;
					options[e.key()] = e.value();
				}

			}

			if (should_save)
			{
				LOG(INFO) << "Updating settings.";
				save();
			}

			return true;
		}

	private:
		bool write_default_config()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += "\\BigBaseV2\\settings.json";

			std::ofstream file(settings_file, std::ios::out);
			file << default_options.dump(4);
			file.close();

			options.clear();
			options = default_options;

			return true;
		}
	};

	inline settings g_settings;
}
