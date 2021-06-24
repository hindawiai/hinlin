<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2005, 2012 IBM Corporation
 *
 * Authors:
 *	Kent Yoder <key@linux.vnet.ibm.com>
 *	Seiji Munetoh <munetoh@jp.ibm.com>
 *	Stefan Berger <stefanb@us.ibm.com>
 *	Reiner Sailer <sailer@watson.ibm.com>
 *	Kylene Hall <kjhall@us.ibm.com>
 *	Nayna Jain <nayna@linux.vnet.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Access to the event log created by a प्रणाली's firmware / BIOS
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/efi.h>
#समावेश <linux/fs.h>
#समावेश <linux/security.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/tpm_eventlog.h>

#समावेश "../tpm.h"
#समावेश "common.h"


अटल स्थिर अक्षर* tcpa_event_type_strings[] = अणु
	"PREBOOT",
	"POST CODE",
	"",
	"NO ACTION",
	"SEPARATOR",
	"ACTION",
	"EVENT TAG",
	"S-CRTM Contents",
	"S-CRTM Version",
	"CPU Microcode",
	"Platform Config Flags",
	"Table of Devices",
	"Compact Hash",
	"IPL",
	"IPL Partition Data",
	"Non-Host Code",
	"Non-Host Config",
	"Non-Host Info"
पूर्ण;

अटल स्थिर अक्षर* tcpa_pc_event_id_strings[] = अणु
	"",
	"SMBIOS",
	"BIS Certificate",
	"POST BIOS ",
	"ESCD ",
	"CMOS",
	"NVRAM",
	"Option ROM",
	"Option ROM config",
	"",
	"Option ROM microcode ",
	"S-CRTM Version",
	"S-CRTM Contents ",
	"POST Contents ",
	"Table of Devices",
पूर्ण;

/* वापसs poपूर्णांकer to start of pos. entry of tcg log */
अटल व्योम *tpm1_bios_measurements_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	loff_t i = 0;
	काष्ठा tpm_chip *chip = m->निजी;
	काष्ठा tpm_bios_log *log = &chip->log;
	व्योम *addr = log->bios_event_log;
	व्योम *limit = log->bios_event_log_end;
	काष्ठा tcpa_event *event;
	u32 converted_event_size;
	u32 converted_event_type;

	/* पढ़ो over *pos measurements */
	करो अणु
		event = addr;

		/* check अगर current entry is valid */
		अगर (addr + माप(काष्ठा tcpa_event) > limit)
			वापस शून्य;

		converted_event_size =
		    करो_endian_conversion(event->event_size);
		converted_event_type =
		    करो_endian_conversion(event->event_type);

		अगर (((converted_event_type == 0) && (converted_event_size == 0))
		    || ((addr + माप(काष्ठा tcpa_event) + converted_event_size)
			> limit))
			वापस शून्य;

		अगर (i++ == *pos)
			अवरोध;

		addr += (माप(काष्ठा tcpa_event) + converted_event_size);
	पूर्ण जबतक (1);

	वापस addr;
पूर्ण

अटल व्योम *tpm1_bios_measurements_next(काष्ठा seq_file *m, व्योम *v,
					loff_t *pos)
अणु
	काष्ठा tcpa_event *event = v;
	काष्ठा tpm_chip *chip = m->निजी;
	काष्ठा tpm_bios_log *log = &chip->log;
	व्योम *limit = log->bios_event_log_end;
	u32 converted_event_size;
	u32 converted_event_type;

	(*pos)++;
	converted_event_size = करो_endian_conversion(event->event_size);

	v += माप(काष्ठा tcpa_event) + converted_event_size;

	/* now check अगर current entry is valid */
	अगर ((v + माप(काष्ठा tcpa_event)) > limit)
		वापस शून्य;

	event = v;

	converted_event_size = करो_endian_conversion(event->event_size);
	converted_event_type = करो_endian_conversion(event->event_type);

	अगर (((converted_event_type == 0) && (converted_event_size == 0)) ||
	    ((v + माप(काष्ठा tcpa_event) + converted_event_size) > limit))
		वापस शून्य;

	वापस v;
पूर्ण

अटल व्योम tpm1_bios_measurements_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक get_event_name(अक्षर *dest, काष्ठा tcpa_event *event,
			अचिन्हित अक्षर * event_entry)
अणु
	स्थिर अक्षर *name = "";
	/* 41 so there is room क्रम 40 data and 1 nul */
	अक्षर data[41] = "";
	पूर्णांक i, n_len = 0, d_len = 0;
	काष्ठा tcpa_pc_event *pc_event;

	चयन (करो_endian_conversion(event->event_type)) अणु
	हाल PREBOOT:
	हाल POST_CODE:
	हाल UNUSED:
	हाल NO_ACTION:
	हाल SCRTM_CONTENTS:
	हाल SCRTM_VERSION:
	हाल CPU_MICROCODE:
	हाल PLATFORM_CONFIG_FLAGS:
	हाल TABLE_OF_DEVICES:
	हाल COMPACT_HASH:
	हाल IPL:
	हाल IPL_PARTITION_DATA:
	हाल NONHOST_CODE:
	हाल NONHOST_CONFIG:
	हाल NONHOST_INFO:
		name = tcpa_event_type_strings[करो_endian_conversion
						(event->event_type)];
		n_len = म_माप(name);
		अवरोध;
	हाल SEPARATOR:
	हाल ACTION:
		अगर (MAX_TEXT_EVENT >
		    करो_endian_conversion(event->event_size)) अणु
			name = event_entry;
			n_len = करो_endian_conversion(event->event_size);
		पूर्ण
		अवरोध;
	हाल EVENT_TAG:
		pc_event = (काष्ठा tcpa_pc_event *)event_entry;

		/* ToDo Row data -> Base64 */

		चयन (करो_endian_conversion(pc_event->event_id)) अणु
		हाल SMBIOS:
		हाल BIS_CERT:
		हाल CMOS:
		हाल NVRAM:
		हाल OPTION_ROM_EXEC:
		हाल OPTION_ROM_CONFIG:
		हाल S_CRTM_VERSION:
			name = tcpa_pc_event_id_strings[करो_endian_conversion
							(pc_event->event_id)];
			n_len = म_माप(name);
			अवरोध;
		/* hash data */
		हाल POST_BIOS_ROM:
		हाल ESCD:
		हाल OPTION_ROM_MICROCODE:
		हाल S_CRTM_CONTENTS:
		हाल POST_CONTENTS:
			name = tcpa_pc_event_id_strings[करो_endian_conversion
							(pc_event->event_id)];
			n_len = म_माप(name);
			क्रम (i = 0; i < 20; i++)
				d_len += प्र_लिखो(&data[2*i], "%02x",
						pc_event->event_data[i]);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस snम_लिखो(dest, MAX_TEXT_EVENT, "[%.*s%.*s]",
			n_len, name, d_len, data);

पूर्ण

अटल पूर्णांक tpm1_binary_bios_measurements_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा tcpa_event *event = v;
	काष्ठा tcpa_event temp_event;
	अक्षर *temp_ptr;
	पूर्णांक i;

	स_नकल(&temp_event, event, माप(काष्ठा tcpa_event));

	/* convert raw पूर्णांकegers क्रम endianness */
	temp_event.pcr_index = करो_endian_conversion(event->pcr_index);
	temp_event.event_type = करो_endian_conversion(event->event_type);
	temp_event.event_size = करो_endian_conversion(event->event_size);

	temp_ptr = (अक्षर *) &temp_event;

	क्रम (i = 0; i < (माप(काष्ठा tcpa_event) - 1) ; i++)
		seq_अ_दो(m, temp_ptr[i]);

	temp_ptr = (अक्षर *) v;

	क्रम (i = (माप(काष्ठा tcpa_event) - 1);
	     i < (माप(काष्ठा tcpa_event) + temp_event.event_size); i++)
		seq_अ_दो(m, temp_ptr[i]);

	वापस 0;

पूर्ण

अटल पूर्णांक tpm1_ascii_bios_measurements_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक len = 0;
	अक्षर *eventname;
	काष्ठा tcpa_event *event = v;
	अचिन्हित अक्षर *event_entry =
	    (अचिन्हित अक्षर *)(v + माप(काष्ठा tcpa_event));

	eventname = kदो_स्मृति(MAX_TEXT_EVENT, GFP_KERNEL);
	अगर (!eventname) अणु
		prपूर्णांकk(KERN_ERR "%s: ERROR - No Memory for event name\n ",
		       __func__);
		वापस -EFAULT;
	पूर्ण

	/* 1st: PCR */
	seq_म_लिखो(m, "%2d ", करो_endian_conversion(event->pcr_index));

	/* 2nd: SHA1 */
	seq_म_लिखो(m, "%20phN", event->pcr_value);

	/* 3rd: event type identअगरier */
	seq_म_लिखो(m, " %02x", करो_endian_conversion(event->event_type));

	len += get_event_name(eventname, event, event_entry);

	/* 4th: eventname <= max + \'0' delimiter */
	seq_म_लिखो(m, " %s\n", eventname);

	kमुक्त(eventname);
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations tpm1_ascii_b_measurements_seqops = अणु
	.start = tpm1_bios_measurements_start,
	.next = tpm1_bios_measurements_next,
	.stop = tpm1_bios_measurements_stop,
	.show = tpm1_ascii_bios_measurements_show,
पूर्ण;

स्थिर काष्ठा seq_operations tpm1_binary_b_measurements_seqops = अणु
	.start = tpm1_bios_measurements_start,
	.next = tpm1_bios_measurements_next,
	.stop = tpm1_bios_measurements_stop,
	.show = tpm1_binary_bios_measurements_show,
पूर्ण;
