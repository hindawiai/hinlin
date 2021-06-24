<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sysfs.c sysfs ABI access functions क्रम TMON program
 *
 * Copyright (C) 2013 Intel Corporation. All rights reserved.
 *
 * Author: Jacob Pan <jacob.jun.pan@linux.पूर्णांकel.com>
 */
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानक_निवेशt.h>
#समावेश <dirent.h>
#समावेश <libपूर्णांकl.h>
#समावेश <प्रकार.स>
#समावेश <समय.स>
#समावेश <syslog.h>
#समावेश <sys/समय.स>
#समावेश <त्रुटिसं.स>

#समावेश "tmon.h"

काष्ठा पंचांगon_platक्रमm_data ptdata;
स्थिर अक्षर *trip_type_name[] = अणु
	"critical",
	"hot",
	"passive",
	"active",
पूर्ण;

पूर्णांक sysfs_set_uदीर्घ(अक्षर *path, अक्षर *filename, अचिन्हित दीर्घ val)
अणु
	खाता *fd;
	पूर्णांक ret = -1;
	अक्षर filepath[256];

	snम_लिखो(filepath, 256, "%s/%s", path, filename);

	fd = ख_खोलो(filepath, "w");
	अगर (!fd) अणु
		syslog(LOG_ERR, "Err: open %s: %s\n", __func__, filepath);
		वापस ret;
	पूर्ण
	ret = ख_लिखो(fd, "%lu", val);
	ख_बंद(fd);

	वापस 0;
पूर्ण

/* history of thermal data, used क्रम control algo */
#घोषणा NR_THERMAL_RECORDS 3
काष्ठा thermal_data_record trec[NR_THERMAL_RECORDS];
पूर्णांक cur_thermal_record; /* index to the trec array */

अटल पूर्णांक sysfs_get_uदीर्घ(अक्षर *path, अक्षर *filename, अचिन्हित दीर्घ *p_uदीर्घ)
अणु
	खाता *fd;
	पूर्णांक ret = -1;
	अक्षर filepath[256];

	snम_लिखो(filepath, 256, "%s/%s", path, filename);

	fd = ख_खोलो(filepath, "r");
	अगर (!fd) अणु
		syslog(LOG_ERR, "Err: open %s: %s\n", __func__, filepath);
		वापस ret;
	पूर्ण
	ret = ख_पूछो(fd, "%lu", p_uदीर्घ);
	ख_बंद(fd);

	वापस 0;
पूर्ण

अटल पूर्णांक sysfs_get_string(अक्षर *path, अक्षर *filename, अक्षर *str)
अणु
	खाता *fd;
	पूर्णांक ret = -1;
	अक्षर filepath[256];

	snम_लिखो(filepath, 256, "%s/%s", path, filename);

	fd = ख_खोलो(filepath, "r");
	अगर (!fd) अणु
		syslog(LOG_ERR, "Err: open %s: %s\n", __func__, filepath);
		वापस ret;
	पूर्ण
	ret = ख_पूछो(fd, "%256s", str);
	ख_बंद(fd);

	वापस ret;
पूर्ण

/* get states of the cooling device instance */
अटल पूर्णांक probe_cdev(काष्ठा cdev_info *cdi, अक्षर *path)
अणु
	sysfs_get_string(path, "type", cdi->type);
	sysfs_get_uदीर्घ(path, "max_state",  &cdi->max_state);
	sysfs_get_uदीर्घ(path, "cur_state", &cdi->cur_state);

	syslog(LOG_INFO, "%s: %s: type %s, max %lu, curr %lu inst %d\n",
		__func__, path,
		cdi->type, cdi->max_state, cdi->cur_state, cdi->instance);

	वापस 0;
पूर्ण

अटल पूर्णांक str_to_trip_type(अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_THERMAL_TRIP_TYPE; i++) अणु
		अगर (!म_भेद(name, trip_type_name[i]))
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/* scan and fill in trip poपूर्णांक info क्रम a thermal zone and trip poपूर्णांक id */
अटल पूर्णांक get_trip_poपूर्णांक_data(अक्षर *tz_path, पूर्णांक tzid, पूर्णांक tpid)
अणु
	अक्षर filename[256];
	अक्षर temp_str[256];
	पूर्णांक trip_type;

	अगर (tpid >= MAX_NR_TRIP)
		वापस -EINVAL;
	/* check trip poपूर्णांक type */
	snम_लिखो(filename, माप(filename), "trip_point_%d_type", tpid);
	sysfs_get_string(tz_path, filename, temp_str);
	trip_type = str_to_trip_type(temp_str);
	अगर (trip_type < 0) अणु
		syslog(LOG_ERR, "%s:%s no matching type\n", __func__, temp_str);
		वापस -ENOENT;
	पूर्ण
	ptdata.tzi[tzid].tp[tpid].type = trip_type;
	syslog(LOG_INFO, "%s:tz:%d tp:%d:type:%s type id %d\n", __func__, tzid,
		tpid, temp_str, trip_type);

	/* TODO: check attribute */

	वापस 0;
पूर्ण

/* वापस instance id क्रम file क्रमmat such as trip_poपूर्णांक_4_temp */
अटल पूर्णांक get_instance_id(अक्षर *name, पूर्णांक pos, पूर्णांक skip)
अणु
	अक्षर *ch;
	पूर्णांक i = 0;

	ch = म_मोहर(name, "_");
	जबतक (ch != शून्य) अणु
		++i;
		syslog(LOG_INFO, "%s:%s:%s:%d", __func__, name, ch, i);
		ch = म_मोहर(शून्य, "_");
		अगर (pos == i)
			वापस म_से_द(ch + skip);
	पूर्ण

	वापस -1;
पूर्ण

/* Find trip poपूर्णांक info of a thermal zone */
अटल पूर्णांक find_tzone_tp(अक्षर *tz_name, अक्षर *d_name, काष्ठा tz_info *tzi,
			पूर्णांक tz_id)
अणु
	पूर्णांक tp_id;
	अचिन्हित दीर्घ temp_uदीर्घ;

	अगर (म_माला(d_name, "trip_point") &&
		म_माला(d_name, "temp")) अणु
		/* check अगर trip poपूर्णांक temp is non-zero
		 * ignore 0/invalid trip poपूर्णांकs
		 */
		sysfs_get_uदीर्घ(tz_name, d_name, &temp_uदीर्घ);
		अगर (temp_uदीर्घ < MAX_TEMP_KC) अणु
			tzi->nr_trip_pts++;
			/* found a valid trip poपूर्णांक */
			tp_id = get_instance_id(d_name, 2, 0);
			syslog(LOG_DEBUG, "tzone %s trip %d temp %lu tpnode %s",
				tz_name, tp_id, temp_uदीर्घ, d_name);
			अगर (tp_id < 0 || tp_id >= MAX_NR_TRIP) अणु
				syslog(LOG_ERR, "Failed to find TP inst %s\n",
					d_name);
				वापस -1;
			पूर्ण
			get_trip_poपूर्णांक_data(tz_name, tz_id, tp_id);
			tzi->tp[tp_id].temp = temp_uदीर्घ;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* check cooling devices क्रम binding info. */
अटल पूर्णांक find_tzone_cdev(काष्ठा dirent *nl, अक्षर *tz_name,
			काष्ठा tz_info *tzi, पूर्णांक tz_id, पूर्णांक cid)
अणु
	अचिन्हित दीर्घ trip_instance = 0;
	अक्षर cdev_name_linked[256];
	अक्षर cdev_name[256];
	अक्षर cdev_trip_name[256];
	पूर्णांक cdev_id;

	अगर (nl->d_type == DT_LNK) अणु
		syslog(LOG_DEBUG, "TZ%d: cdev: %s cid %d\n", tz_id, nl->d_name,
			cid);
		tzi->nr_cdev++;
		अगर (tzi->nr_cdev > ptdata.nr_cooling_dev) अणु
			syslog(LOG_ERR, "Err: Too many cdev? %d\n",
				tzi->nr_cdev);
			वापस -EINVAL;
		पूर्ण
		/* find the link to real cooling device record binding */
		snम_लिखो(cdev_name, 256, "%s/%s", tz_name, nl->d_name);
		स_रखो(cdev_name_linked, 0, माप(cdev_name_linked));
		अगर (पढ़ोlink(cdev_name, cdev_name_linked,
				माप(cdev_name_linked) - 1) != -1) अणु
			cdev_id = get_instance_id(cdev_name_linked, 1,
						माप("device") - 1);
			syslog(LOG_DEBUG, "cdev %s linked to %s : %d\n",
				cdev_name, cdev_name_linked, cdev_id);
			tzi->cdev_binding |= (1 << cdev_id);

			/* find the trip poपूर्णांक in which the cdev is binded to
			 * in this tzone
			 */
			snम_लिखो(cdev_trip_name, 256, "%s%s", nl->d_name,
				"_trip_point");
			sysfs_get_uदीर्घ(tz_name, cdev_trip_name,
					&trip_instance);
			/* validate trip poपूर्णांक range, e.g. trip could वापस -1
			 * when passive is enabled
			 */
			अगर (trip_instance > MAX_NR_TRIP)
				trip_instance = 0;
			tzi->trip_binding[cdev_id] |= 1 << trip_instance;
			syslog(LOG_DEBUG, "cdev %s -> trip:%lu: 0x%lx %d\n",
				cdev_name, trip_instance,
				tzi->trip_binding[cdev_id],
				cdev_id);


		पूर्ण
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण



/*****************************************************************************
 * Beक्रमe calling scan_tzones, thermal sysfs must be probed to determine
 * the number of thermal zones and cooling devices.
 * We loop through each thermal zone and fill in tz_info काष्ठा, i.e.
 * ptdata.tzi[]
root@jacob-chiefriver:~# tree -d /sys/class/thermal/thermal_zone0
/sys/class/thermal/thermal_zone0
|-- cdev0 -> ../cooling_device4
|-- cdev1 -> ../cooling_device3
|-- cdev10 -> ../cooling_device7
|-- cdev11 -> ../cooling_device6
|-- cdev12 -> ../cooling_device5
|-- cdev2 -> ../cooling_device2
|-- cdev3 -> ../cooling_device1
|-- cdev4 -> ../cooling_device0
|-- cdev5 -> ../cooling_device12
|-- cdev6 -> ../cooling_device11
|-- cdev7 -> ../cooling_device10
|-- cdev8 -> ../cooling_device9
|-- cdev9 -> ../cooling_device8
|-- device -> ../../../LNXSYSTM:00/device:62/LNXTHERM:00
|-- घातer
`-- subप्रणाली -> ../../../../class/thermal
*****************************************************************************/
अटल पूर्णांक scan_tzones(व्योम)
अणु
	सूची *dir;
	काष्ठा dirent **namelist;
	अक्षर tz_name[256];
	पूर्णांक i, j, n, k = 0;

	अगर (!ptdata.nr_tz_sensor)
		वापस -1;

	क्रम (i = 0; i <= ptdata.max_tz_instance; i++) अणु
		स_रखो(tz_name, 0, माप(tz_name));
		snम_लिखो(tz_name, 256, "%s/%s%d", THERMAL_SYSFS, TZONE, i);

		dir = सूची_खोलो(tz_name);
		अगर (!dir) अणु
			syslog(LOG_INFO, "Thermal zone %s skipped\n", tz_name);
			जारी;
		पूर्ण
		/* keep track of valid tzones */
		n = scandir(tz_name, &namelist, 0, alphasort);
		अगर (n < 0)
			syslog(LOG_ERR, "scandir failed in %s",  tz_name);
		अन्यथा अणु
			sysfs_get_string(tz_name, "type", ptdata.tzi[k].type);
			ptdata.tzi[k].instance = i;
			/* detect trip poपूर्णांकs and cdev attached to this tzone */
			j = 0; /* index क्रम cdev */
			ptdata.tzi[k].nr_cdev = 0;
			ptdata.tzi[k].nr_trip_pts = 0;
			जबतक (n--) अणु
				अक्षर *temp_str;

				अगर (find_tzone_tp(tz_name, namelist[n]->d_name,
							&ptdata.tzi[k], k))
					अवरोध;
				temp_str = म_माला(namelist[n]->d_name, "cdev");
				अगर (!temp_str) अणु
					मुक्त(namelist[n]);
					जारी;
				पूर्ण
				अगर (!find_tzone_cdev(namelist[n], tz_name,
							&ptdata.tzi[k], i, j))
					j++; /* increment cdev index */
				मुक्त(namelist[n]);
			पूर्ण
			मुक्त(namelist);
		पूर्ण
		/*TODO: reverse trip poपूर्णांकs */
		बंद_सूची(dir);
		syslog(LOG_INFO, "TZ %d has %d cdev\n",	i,
			ptdata.tzi[k].nr_cdev);
		k++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक scan_cdevs(व्योम)
अणु
	सूची *dir;
	काष्ठा dirent **namelist;
	अक्षर cdev_name[256];
	पूर्णांक i, n, k = 0;

	अगर (!ptdata.nr_cooling_dev) अणु
		ख_लिखो(मानक_त्रुटि, "No cooling devices found\n");
		वापस 0;
	पूर्ण
	क्रम (i = 0; i <= ptdata.max_cdev_instance; i++) अणु
		स_रखो(cdev_name, 0, माप(cdev_name));
		snम_लिखो(cdev_name, 256, "%s/%s%d", THERMAL_SYSFS, CDEV, i);

		dir = सूची_खोलो(cdev_name);
		अगर (!dir) अणु
			syslog(LOG_INFO, "Cooling dev %s skipped\n", cdev_name);
			/* there is a gap in cooling device id, check again
			 * क्रम the same index.
			 */
			जारी;
		पूर्ण

		n = scandir(cdev_name, &namelist, 0, alphasort);
		अगर (n < 0)
			syslog(LOG_ERR, "scandir failed in %s",  cdev_name);
		अन्यथा अणु
			sysfs_get_string(cdev_name, "type", ptdata.cdi[k].type);
			ptdata.cdi[k].instance = i;
			अगर (म_माला(ptdata.cdi[k].type, ctrl_cdev)) अणु
				ptdata.cdi[k].flag |= CDEV_FLAG_IN_CONTROL;
				syslog(LOG_DEBUG, "control cdev id %d\n", i);
			पूर्ण
			जबतक (n--)
				मुक्त(namelist[n]);
			मुक्त(namelist);
		पूर्ण
		बंद_सूची(dir);
		k++;
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक probe_thermal_sysfs(व्योम)
अणु
	सूची *dir;
	काष्ठा dirent **namelist;
	पूर्णांक n;

	dir = सूची_खोलो(THERMAL_SYSFS);
	अगर (!dir) अणु
		ख_लिखो(मानक_त्रुटि, "\nNo thermal sysfs, exit\n");
		वापस -1;
	पूर्ण
	n = scandir(THERMAL_SYSFS, &namelist, 0, alphasort);
	अगर (n < 0)
		syslog(LOG_ERR, "scandir failed in thermal sysfs");
	अन्यथा अणु
		/* detect number of thermal zones and cooling devices */
		जबतक (n--) अणु
			पूर्णांक inst;

			अगर (म_माला(namelist[n]->d_name, CDEV)) अणु
				inst = get_instance_id(namelist[n]->d_name, 1,
						माप("device") - 1);
				/* keep track of the max cooling device since
				 * there may be gaps.
				 */
				अगर (inst > ptdata.max_cdev_instance)
					ptdata.max_cdev_instance = inst;

				syslog(LOG_DEBUG, "found cdev: %s %d %d\n",
					namelist[n]->d_name,
					ptdata.nr_cooling_dev,
					ptdata.max_cdev_instance);
				ptdata.nr_cooling_dev++;
			पूर्ण अन्यथा अगर (म_माला(namelist[n]->d_name, TZONE)) अणु
				inst = get_instance_id(namelist[n]->d_name, 1,
						माप("zone") - 1);
				अगर (inst > ptdata.max_tz_instance)
					ptdata.max_tz_instance = inst;

				syslog(LOG_DEBUG, "found tzone: %s %d %d\n",
					namelist[n]->d_name,
					ptdata.nr_tz_sensor,
					ptdata.max_tz_instance);
				ptdata.nr_tz_sensor++;
			पूर्ण
			मुक्त(namelist[n]);
		पूर्ण
		मुक्त(namelist);
	पूर्ण
	syslog(LOG_INFO, "found %d tzone(s), %d cdev(s), target zone %d\n",
		ptdata.nr_tz_sensor, ptdata.nr_cooling_dev,
		target_thermal_zone);
	बंद_सूची(dir);

	अगर (!ptdata.nr_tz_sensor) अणु
		ख_लिखो(मानक_त्रुटि, "\nNo thermal zones found, exit\n\n");
		वापस -1;
	पूर्ण

	ptdata.tzi = सुस्मृति(ptdata.max_tz_instance+1, माप(काष्ठा tz_info));
	अगर (!ptdata.tzi) अणु
		ख_लिखो(मानक_त्रुटि, "Err: allocate tz_info\n");
		वापस -1;
	पूर्ण

	/* we still show thermal zone inक्रमmation अगर there is no cdev */
	अगर (ptdata.nr_cooling_dev) अणु
		ptdata.cdi = सुस्मृति(ptdata.max_cdev_instance + 1,
				माप(काष्ठा cdev_info));
		अगर (!ptdata.cdi) अणु
			मुक्त(ptdata.tzi);
			ख_लिखो(मानक_त्रुटि, "Err: allocate cdev_info\n");
			वापस -1;
		पूर्ण
	पूर्ण

	/* now probe tzones */
	अगर (scan_tzones())
		वापस -1;
	अगर (scan_cdevs())
		वापस -1;
	वापस 0;
पूर्ण

/* convert sysfs zone instance to zone array index */
पूर्णांक zone_instance_to_index(पूर्णांक zone_inst)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ptdata.nr_tz_sensor; i++)
		अगर (ptdata.tzi[i].instance == zone_inst)
			वापस i;
	वापस -ENOENT;
पूर्ण

/* पढ़ो temperature of all thermal zones */
पूर्णांक update_thermal_data()
अणु
	पूर्णांक i;
	पूर्णांक next_thermal_record = cur_thermal_record + 1;
	अक्षर tz_name[256];
	अटल अचिन्हित दीर्घ samples;

	अगर (!ptdata.nr_tz_sensor) अणु
		syslog(LOG_ERR, "No thermal zones found!\n");
		वापस -1;
	पूर्ण

	/* circular buffer क्रम keeping historic data */
	अगर (next_thermal_record >= NR_THERMAL_RECORDS)
		next_thermal_record = 0;
	समय_लोofday(&trec[next_thermal_record].tv, शून्य);
	अगर (पंचांगon_log) अणु
		ख_लिखो(पंचांगon_log, "%lu ", ++samples);
		ख_लिखो(पंचांगon_log, "%3.1f ", p_param.t_target);
	पूर्ण
	क्रम (i = 0; i < ptdata.nr_tz_sensor; i++) अणु
		स_रखो(tz_name, 0, माप(tz_name));
		snम_लिखो(tz_name, 256, "%s/%s%d", THERMAL_SYSFS, TZONE,
			ptdata.tzi[i].instance);
		sysfs_get_uदीर्घ(tz_name, "temp",
				&trec[next_thermal_record].temp[i]);
		अगर (पंचांगon_log)
			ख_लिखो(पंचांगon_log, "%lu ",
				trec[next_thermal_record].temp[i] / 1000);
	पूर्ण
	cur_thermal_record = next_thermal_record;
	क्रम (i = 0; i < ptdata.nr_cooling_dev; i++) अणु
		अक्षर cdev_name[256];
		अचिन्हित दीर्घ val;

		snम_लिखो(cdev_name, 256, "%s/%s%d", THERMAL_SYSFS, CDEV,
			ptdata.cdi[i].instance);
		probe_cdev(&ptdata.cdi[i], cdev_name);
		val = ptdata.cdi[i].cur_state;
		अगर (val > 1000000)
			val = 0;
		अगर (पंचांगon_log)
			ख_लिखो(पंचांगon_log, "%lu ", val);
	पूर्ण

	अगर (पंचांगon_log) अणु
		ख_लिखो(पंचांगon_log, "\n");
		ख_साफ(पंचांगon_log);
	पूर्ण

	वापस 0;
पूर्ण

व्योम set_ctrl_state(अचिन्हित दीर्घ state)
अणु
	अक्षर ctrl_cdev_path[256];
	पूर्णांक i;
	अचिन्हित दीर्घ cdev_state;

	अगर (no_control)
		वापस;
	/* set all ctrl cdev to the same state */
	क्रम (i = 0; i < ptdata.nr_cooling_dev; i++) अणु
		अगर (ptdata.cdi[i].flag & CDEV_FLAG_IN_CONTROL) अणु
			अगर (ptdata.cdi[i].max_state < 10) अणु
				म_नकल(ctrl_cdev, "None.");
				वापस;
			पूर्ण
			/* scale to percentage of max_state */
			cdev_state = state * ptdata.cdi[i].max_state/100;
			syslog(LOG_DEBUG,
				"ctrl cdev %d set state %lu scaled to %lu\n",
				ptdata.cdi[i].instance, state, cdev_state);
			snम_लिखो(ctrl_cdev_path, 256, "%s/%s%d", THERMAL_SYSFS,
				CDEV, ptdata.cdi[i].instance);
			syslog(LOG_DEBUG, "ctrl cdev path %s", ctrl_cdev_path);
			sysfs_set_uदीर्घ(ctrl_cdev_path, "cur_state",
					cdev_state);
		पूर्ण
	पूर्ण
पूर्ण

व्योम get_ctrl_state(अचिन्हित दीर्घ *state)
अणु
	अक्षर ctrl_cdev_path[256];
	पूर्णांक ctrl_cdev_id = -1;
	पूर्णांक i;

	/* TODO: take average of all ctrl types. also consider change based on
	 * uevent. Take the first पढ़ोing क्रम now.
	 */
	क्रम (i = 0; i < ptdata.nr_cooling_dev; i++) अणु
		अगर (ptdata.cdi[i].flag & CDEV_FLAG_IN_CONTROL) अणु
			ctrl_cdev_id = ptdata.cdi[i].instance;
			syslog(LOG_INFO, "ctrl cdev %d get state\n",
				ptdata.cdi[i].instance);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ctrl_cdev_id == -1) अणु
		*state = 0;
		वापस;
	पूर्ण
	snम_लिखो(ctrl_cdev_path, 256, "%s/%s%d", THERMAL_SYSFS,
		CDEV, ctrl_cdev_id);
	sysfs_get_uदीर्घ(ctrl_cdev_path, "cur_state", state);
पूर्ण

व्योम मुक्त_thermal_data(व्योम)
अणु
	मुक्त(ptdata.tzi);
	मुक्त(ptdata.cdi);
पूर्ण
