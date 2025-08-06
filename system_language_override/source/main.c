// Author: jocover @ https://github.com/jocover
// Author: Kendek @ https://github.com/KrisztianKende
// Repository: https://github.com/GoldHEN/GoldHEN_Plugins_Repository

#include <stdbool.h>
#include "plugin_common.h"
#include "Common.h"

attr_public const char *g_pluginName = "system_language_override";
attr_public const char *g_pluginDesc = "Override In-Game System Language";
attr_public const char *g_pluginAuth = "jocover, Kendek";
attr_public u32 g_pluginVersion = 0x00000100; // 1.00

s32 (*sceSystemServiceParamGetInt)(s32 paramId, s32 *value);

HOOK_INIT(sceSystemServiceParamGetInt);

s8 lang = -2;

bool get_lang() {
    struct proc_info procInfo;

    if (sys_sdk_proc_info(&procInfo) == 0) {
        FILE *plugins_ini = fopen(GOLDHEN_PATH "/plugins.ini", "r");

        if (plugins_ini) {
            bool in_section = false;
            char buf[219];

            while (fgets(buf, sizeof(buf) - 18, plugins_ini)) {
                char *line = buf;
again:
                switch (line[0]) {
                    case ' ':
                        ++line;
                        goto again;
                    case '[': {
                        u8 len = strlen(line);

                        if (len > 10 && line[10] == ']') {
                            line[10] = '\0';
                            in_section = strcmp(line + 1, procInfo.titleid) == 0;
                        }
                        else if (len > 8) {
                            line[9] = '\0';
                            in_section = strcmp(line, "[default]") == 0;
                        }
                        else
                            in_section = false;

                        break;
                    }
                    case '/':
                        if (! in_section) break;
                        char *in_line = strstr(line, "/system_language_override.prx");
                        if (! in_line) break;
                        char *is_cmt = strstr(line, ";");
                        if (! is_cmt) break;
                        u8 len = strlen(is_cmt);
                        if (len < 3 || strlen(in_line) < len) break;
                        char *val = in_line + 29;
                        val[20] = '\0';
                        while (val[0] == ' ') ++val;
                        if (val++ != is_cmt) break;
                        while (val[0] == ' ') ++val;
                        if (strlen(val) < 2) break;

                        if (val[2] == '_')
                            val[5] = '\0';
                        else
                            val[2] = '\0';

                        char *lang_codes[] = { "ja", "en_US", "fr_FR", "es_ES", "de", "it", "nl", "pt_PT", "ru", "ko", "zh_TW", "zh_CN", "fi", "sv", "da", "no", "pl", "pt_BR", "en_GB", "tr", "es_LA", "ar", "fr_CA", "cs", "hu", "el", "ro", "th", "vi", "in", "uk" };

                        for (u8 i = 0; i < 31; i++)
                            if (strcmp(val, lang_codes[i]) == 0) {
                                lang = i;
                                final_printf("Override In-Game System Language: %s\n", lang_codes[i]);
                                goto found;
                            }
                }
            }
found:
            fclose(plugins_ini);
        }
    }

    return lang == -2 ? ! ++lang : true;
}

s32 sceSystemServiceParamGetInt_hook(s32 paramId, s32 *value) {
    s32 rv = HOOK_CONTINUE(sceSystemServiceParamGetInt, s32(*)(s32, s32 *), paramId, value);

    if (paramId == 1 && (lang > -1 || (lang == -2 && get_lang()))) {
        *value = lang;
    }

    return rv;
}

s32 attr_public plugin_load(s32 argc, const char* argv[]) {
    final_printf("[GoldHEN] <%s\\Ver.0x%08x> %s\n", g_pluginName, g_pluginVersion, __func__);
    final_printf("[GoldHEN] Plugin Author(s): %s\n", g_pluginAuth);
    boot_ver();
    s32 h = 0;
    sys_dynlib_load_prx("libSceSystemService.sprx", &h);
    sys_dynlib_dlsym(h, "sceSystemServiceParamGetInt", &sceSystemServiceParamGetInt);
    HOOK32(sceSystemServiceParamGetInt);
    return 0;
}

s32 attr_public plugin_unload(s32 argc, const char* argv[]) {
    final_printf("[GoldHEN] <%s\\Ver.0x%08x> %s\n", g_pluginName, g_pluginVersion, __func__);
    UNHOOK(sceSystemServiceParamGetInt);
    return 0;
}

s32 attr_module_hidden module_start(s64 argc, const void *args)
{
    return 0;
}

s32 attr_module_hidden module_stop(s64 argc, const void *args)
{
    return 0;
}
