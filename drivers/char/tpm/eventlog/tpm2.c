<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 IBM Corporation
 *
 * Authors:
 *      Nayna Jain <nayna@linux.vnet.ibm.com>
 *
 * Access to TPM 2.0 event log as written by Firmware.
 * It assumes that ग_लिखोr of event log has followed TCG Specअगरication
 * क्रम Family "2.0" and written the event data in little endian.
 * With that, it करोesn't need any endian conversion क्रम काष्ठाure
 * content.
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/security.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/tpm_eventlog.h>

#समावेश "../tpm.h"
#समावेश "common.h"

/*
 * calc_tpm2_event_size() - calculate the event size, where event
 * is an entry in the TPM 2.0 event log. The event is of type Crypto
 * Agile Log Entry Format as defined in TCG EFI Protocol Specअगरication
 * Family "2.0".

 * @event: event whose size is to be calculated.
 * @event_header: the first event in the event log.
 *
 * Returns size of the event. If it is an invalid event, वापसs 0.
 */
अटल माप_प्रकार calc_tpm2_event_size(काष्ठा tcg_pcr_event2_head *event,
				   काष्ठा tcg_pcr_event *event_header)
अणु
	वापस __calc_tpm2_event_size(event, event_header, false);
पूर्ण

अटल व्योम *tpm2_bios_measurements_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा tpm_chip *chip = m->निजी;
	काष्ठा tpm_bios_log *log = &chip->log;
	व्योम *addr = log->bios_event_log;
	व्योम *limit = log->bios_event_log_end;
	काष्ठा tcg_pcr_event *event_header;
	काष्ठा tcg_pcr_event2_head *event;
	माप_प्रकार size;
	पूर्णांक i;

	event_header = addr;
	size = काष्ठा_size(event_header, event, event_header->event_size);

	अगर (*pos == 0) अणु
		अगर (addr + size < limit) अणु
			अगर ((event_header->event_type == 0) &&
			    (event_header->event_size == 0))
				वापस शून्य;
			वापस SEQ_START_TOKEN;
		पूर्ण
	पूर्ण

	अगर (*pos > 0) अणु
		addr += size;
		event = addr;
		size = calc_tpm2_event_size(event, event_header);
		अगर ((addr + size >=  limit) || (size == 0))
			वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < (*pos - 1); i++) अणु
		event = addr;
		size = calc_tpm2_event_size(event, event_header);

		अगर ((addr + size >= limit) || (size == 0))
			वापस शून्य;
		addr += size;
	पूर्ण

	वापस addr;
पूर्ण

अटल व्योम *tpm2_bios_measurements_next(काष्ठा seq_file *m, व्योम *v,
					 loff_t *pos)
अणु
	काष्ठा tcg_pcr_event *event_header;
	काष्ठा tcg_pcr_event2_head *event;
	काष्ठा tpm_chip *chip = m->निजी;
	काष्ठा tpm_bios_log *log = &chip->log;
	व्योम *limit = log->bios_event_log_end;
	माप_प्रकार event_size;
	व्योम *marker;

	(*pos)++;
	event_header = log->bios_event_log;

	अगर (v == SEQ_START_TOKEN) अणु
		event_size = काष्ठा_size(event_header, event,
					 event_header->event_size);
		marker = event_header;
	पूर्ण अन्यथा अणु
		event = v;
		event_size = calc_tpm2_event_size(event, event_header);
		अगर (event_size == 0)
			वापस शून्य;
		marker = event;
	पूर्ण

	marker = marker + event_size;
	अगर (marker >= limit)
		वापस शून्य;
	v = marker;
	event = v;

	event_size = calc_tpm2_event_size(event, event_header);
	अगर (((v + event_size) >= limit) || (event_size == 0))
		वापस शून्य;

	वापस v;
पूर्ण

अटल व्योम tpm2_bios_measurements_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक tpm2_binary_bios_measurements_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा tpm_chip *chip = m->निजी;
	काष्ठा tpm_bios_log *log = &chip->log;
	काष्ठा tcg_pcr_event *event_header = log->bios_event_log;
	काष्ठा tcg_pcr_event2_head *event = v;
	व्योम *temp_ptr;
	माप_प्रकार size;

	अगर (v == SEQ_START_TOKEN) अणु
		size = काष्ठा_size(event_header, event,
				   event_header->event_size);
		temp_ptr = event_header;

		अगर (size > 0)
			seq_ग_लिखो(m, temp_ptr, size);
	पूर्ण अन्यथा अणु
		size = calc_tpm2_event_size(event, event_header);
		temp_ptr = event;
		अगर (size > 0)
			seq_ग_लिखो(m, temp_ptr, size);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations tpm2_binary_b_measurements_seqops = अणु
	.start = tpm2_bios_measurements_start,
	.next = tpm2_bios_measurements_next,
	.stop = tpm2_bios_measurements_stop,
	.show = tpm2_binary_bios_measurements_show,
पूर्ण;
