<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * पंचांगon.h contains data काष्ठाures and स्थिरants used by TMON
 *
 * Copyright (C) 2012 Intel Corporation. All rights reserved.
 *
 * Author Name Jacob Pan <jacob.jun.pan@linux.पूर्णांकel.com>
 */

#अगर_अघोषित TMON_H
#घोषणा TMON_H

#घोषणा MAX_DISP_TEMP 125
#घोषणा MAX_CTRL_TEMP 105
#घोषणा MIN_CTRL_TEMP 40
#घोषणा MAX_NR_TZONE 16
#घोषणा MAX_NR_CDEV 32
#घोषणा MAX_NR_TRIP 16
#घोषणा MAX_NR_CDEV_TRIP 12 /* number of cooling devices that can bind
			     * to a thermal zone trip.
			     */
#घोषणा MAX_TEMP_KC 140000
/* starting अक्षर position to draw sensor data, such as tz names
 * trip poपूर्णांक list, etc.
 */
#घोषणा DATA_LEFT_ALIGN 10
#घोषणा NR_LINES_TZDATA 1
#घोषणा TMON_LOG_खाता "/var/tmp/tmon.log"

बाह्य अचिन्हित दीर्घ tickसमय;
बाह्य द्विगुन समय_elapsed;
बाह्य अचिन्हित दीर्घ target_temp_user;
बाह्य पूर्णांक dialogue_on;
बाह्य अक्षर ctrl_cdev[];
बाह्य pthपढ़ो_mutex_t input_lock;
बाह्य पूर्णांक पंचांगon_निकास;
बाह्य पूर्णांक target_thermal_zone;
/* use fixed size record to simplअगरy data processing and transfer
 * TBD: more info to be added, e.g. programmable trip poपूर्णांक data.
*/
काष्ठा thermal_data_record अणु
	काष्ठा समयval tv;
	अचिन्हित दीर्घ temp[MAX_NR_TZONE];
	द्विगुन pid_out_pct;
पूर्ण;

काष्ठा cdev_info अणु
	अक्षर type[64];
	पूर्णांक instance;
	अचिन्हित दीर्घ max_state;
	अचिन्हित दीर्घ cur_state;
	अचिन्हित दीर्घ flag;
पूर्ण;

क्रमागत trip_type अणु
	THERMAL_TRIP_CRITICAL,
	THERMAL_TRIP_HOT,
	THERMAL_TRIP_PASSIVE,
	THERMAL_TRIP_ACTIVE,
	NR_THERMAL_TRIP_TYPE,
पूर्ण;

काष्ठा trip_poपूर्णांक अणु
	क्रमागत trip_type type;
	अचिन्हित दीर्घ temp;
	अचिन्हित दीर्घ hysteresis;
	पूर्णांक attribute; /* programmability etc. */
पूर्ण;

/* thermal zone configuration inक्रमmation, binding with cooling devices could
 * change at runसमय.
 */
काष्ठा tz_info अणु
	अक्षर type[256]; /* e.g. acpitz */
	पूर्णांक instance;
	पूर्णांक passive; /* active zone has passive node to क्रमce passive mode */
	पूर्णांक nr_cdev; /* number of cooling device binded */
	पूर्णांक nr_trip_pts;
	काष्ठा trip_poपूर्णांक tp[MAX_NR_TRIP];
	अचिन्हित दीर्घ cdev_binding; /* biपंचांगap क्रम attached cdevs */
	/* cdev bind trip poपूर्णांकs, allow one cdev bind to multiple trips */
	अचिन्हित दीर्घ trip_binding[MAX_NR_CDEV];
पूर्ण;

काष्ठा पंचांगon_platक्रमm_data अणु
	पूर्णांक nr_tz_sensor;
	पूर्णांक nr_cooling_dev;
	/* keep track of instance ids since there might be gaps */
	पूर्णांक max_tz_instance;
	पूर्णांक max_cdev_instance;
	काष्ठा tz_info *tzi;
	काष्ठा cdev_info *cdi;
पूर्ण;

काष्ठा control_ops अणु
	व्योम (*set_ratio)(अचिन्हित दीर्घ ratio);
	अचिन्हित दीर्घ (*get_ratio)(अचिन्हित दीर्घ ratio);

पूर्ण;

क्रमागत cdev_types अणु
	CDEV_TYPE_PROC,
	CDEV_TYPE_FAN,
	CDEV_TYPE_MEM,
	CDEV_TYPE_NR,
पूर्ण;

/* REVISIT: the idea is to group sensors अगर possible, e.g. on पूर्णांकel mid
 * we have "skin0", "skin1", "sys", "msicdie"
 * on DPTF enabled प्रणालीs, we might have PCH, TSKN, TAMB, etc.
 */
क्रमागत tzone_types अणु
	TZONE_TYPE_ACPI,
	TZONE_TYPE_PCH,
	TZONE_TYPE_NR,
पूर्ण;

/* limit the output of PID controller adjusपंचांगent */
#घोषणा LIMIT_HIGH (95)
#घोषणा LIMIT_LOW  (2)

काष्ठा pid_params अणु
	द्विगुन kp;  /* Controller gain from Dialog Box */
	द्विगुन ki;  /* Time-स्थिरant क्रम I action from Dialog Box */
	द्विगुन kd;  /* Time-स्थिरant क्रम D action from Dialog Box */
	द्विगुन ts;
	द्विगुन k_lpf;

	द्विगुन t_target;
	द्विगुन y_k;
पूर्ण;

बाह्य पूर्णांक init_thermal_controller(व्योम);
बाह्य व्योम controller_handler(स्थिर द्विगुन xk, द्विगुन *yk);

बाह्य काष्ठा पंचांगon_platक्रमm_data ptdata;
बाह्य काष्ठा pid_params p_param;

बाह्य खाता *पंचांगon_log;
बाह्य पूर्णांक cur_thermal_record; /* index to the trec array */
बाह्य काष्ठा thermal_data_record trec[];
बाह्य स्थिर अक्षर *trip_type_name[];
बाह्य अचिन्हित दीर्घ no_control;

बाह्य व्योम initialize_curses(व्योम);
बाह्य व्योम show_controller_stats(अक्षर *line);
बाह्य व्योम show_title_bar(व्योम);
बाह्य व्योम setup_winकरोws(व्योम);
बाह्य व्योम disable_tui(व्योम);
बाह्य व्योम show_sensors_w(व्योम);
बाह्य व्योम show_data_w(व्योम);
बाह्य व्योम ग_लिखो_status_bar(पूर्णांक x, अक्षर *line);
बाह्य व्योम show_control_w();

बाह्य व्योम show_cooling_device(व्योम);
बाह्य व्योम show_dialogue(व्योम);
बाह्य पूर्णांक update_thermal_data(व्योम);

बाह्य पूर्णांक probe_thermal_sysfs(व्योम);
बाह्य व्योम मुक्त_thermal_data(व्योम);
बाह्य	व्योम resize_handler(पूर्णांक sig);
बाह्य व्योम set_ctrl_state(अचिन्हित दीर्घ state);
बाह्य व्योम get_ctrl_state(अचिन्हित दीर्घ *state);
बाह्य व्योम *handle_tui_events(व्योम *arg);
बाह्य पूर्णांक sysfs_set_uदीर्घ(अक्षर *path, अक्षर *filename, अचिन्हित दीर्घ val);
बाह्य पूर्णांक zone_instance_to_index(पूर्णांक zone_inst);
बाह्य व्योम बंद_winकरोws(व्योम);

#घोषणा PT_COLOR_DEFAULT    1
#घोषणा PT_COLOR_HEADER_BAR 2
#घोषणा PT_COLOR_ERROR      3
#घोषणा PT_COLOR_RED        4
#घोषणा PT_COLOR_YELLOW     5
#घोषणा PT_COLOR_GREEN      6
#घोषणा PT_COLOR_BRIGHT     7
#घोषणा PT_COLOR_BLUE	    8

/* each thermal zone uses 12 अक्षरs, 8 क्रम name, 2 क्रम instance, 2 space
 * also used to list trip poपूर्णांकs in क्रमms of AAAC, which represents
 * A: Active
 * C: Critical
 */
#घोषणा TZONE_RECORD_SIZE 12
#घोषणा TZ_LEFT_ALIGN 32
#घोषणा CDEV_NAME_SIZE 20
#घोषणा CDEV_FLAG_IN_CONTROL (1 << 0)

/* dialogue box starts */
#घोषणा DIAG_X 48
#घोषणा DIAG_Y 8
#घोषणा THERMAL_SYSFS "/sys/class/thermal"
#घोषणा CDEV "cooling_device"
#घोषणा TZONE "thermal_zone"
#घोषणा TDATA_LEFT 16
#पूर्ण_अगर /* TMON_H */
