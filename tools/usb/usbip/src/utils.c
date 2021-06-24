<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>

#समावेश "usbip_common.h"
#समावेश "utils.h"
#समावेश "sysfs_utils.h"

पूर्णांक modअगरy_match_busid(अक्षर *busid, पूर्णांक add)
अणु
	अक्षर attr_name[] = "match_busid";
	अक्षर command[SYSFS_BUS_ID_SIZE + 4];
	अक्षर match_busid_attr_path[SYSFS_PATH_MAX];
	पूर्णांक rc;
	पूर्णांक cmd_size;

	snम_लिखो(match_busid_attr_path, माप(match_busid_attr_path),
		 "%s/%s/%s/%s/%s/%s", SYSFS_MNT_PATH, SYSFS_BUS_NAME,
		 SYSFS_BUS_TYPE, SYSFS_DRIVERS_NAME, USBIP_HOST_DRV_NAME,
		 attr_name);

	अगर (add)
		cmd_size = snम_लिखो(command, SYSFS_BUS_ID_SIZE + 4, "add %s",
				    busid);
	अन्यथा
		cmd_size = snम_लिखो(command, SYSFS_BUS_ID_SIZE + 4, "del %s",
				    busid);

	rc = ग_लिखो_sysfs_attribute(match_busid_attr_path, command,
				   cmd_size);
	अगर (rc < 0) अणु
		dbg("failed to write match_busid: %s", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
