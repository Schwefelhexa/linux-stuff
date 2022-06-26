/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * separator           string to echo                  NULL
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */
static const struct arg args[] = {
	/* function format          argument */
	{ cpu_perc, "^c#1b1b1b^ ^b#F26419^   ^c#F26419^ ^b#1b1b1b^ %3s%% / ", NULL },
	{ ram_used, "%s ", NULL },
	{ wifi_essid, "^c#1B2845^ ^b#65AFFF^  ^c#65AFFF^ ^b#1B2845^ %s", "wlan0" },
	{ wifi_perc, " / %3s%%", "wlan0" },
	{ run_command, "^c#1B2845^ ^b#F6AE2D^ \uf578 ^c#F6AE2D^ ^b#1B2845^ %3s%% ", "echo \"scale = 2 ; ($(cat /sys/class/power_supply/BAT1/energy_now) + $(cat /sys/class/power_supply/BAT2/energy_now)) / ($(cat /sys/class/power_supply/BAT1/energy_full) + $(cat /sys/class/power_supply/BAT2/energy_full))\" | bc | sed 's/.//'" },
	{ run_command, "%s ", "[[ $(cat /sys/class/power_supply/BAT2/status) = \"Charging\" ]] && echo \"\" || echo \" \"" },
	{ datetime, "^b#689d6a^ ^c#1b1b1d^  ^b#8ec07c^ ^c#1b1b1d^%s", "%a, %d.%m.%Y %H:%M:%S  " },
};
