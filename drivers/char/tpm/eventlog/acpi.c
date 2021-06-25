<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2005 IBM Corporation
 *
 * Authors:
 *	Seiji Munetoh <munetoh@jp.ibm.com>
 *	Stefan Berger <stefanb@us.ibm.com>
 *	Reiner Sailer <sailer@watson.ibm.com>
 *	Kylene Hall <kjhall@us.ibm.com>
 *	Nayna Jain <nayna@linux.vnet.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Access to the event log extended by the TCG BIOS of PC platक्रमm
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/security.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/tpm_eventlog.h>

#समावेश "../tpm.h"
#समावेश "common.h"

काष्ठा acpi_tcpa अणु
	काष्ठा acpi_table_header hdr;
	u16 platक्रमm_class;
	जोड़ अणु
		काष्ठा client_hdr अणु
			u32 log_max_len __packed;
			u64 log_start_addr __packed;
		पूर्ण client;
		काष्ठा server_hdr अणु
			u16 reserved;
			u64 log_max_len __packed;
			u64 log_start_addr __packed;
		पूर्ण server;
	पूर्ण;
पूर्ण;

/* Check that the given log is indeed a TPM2 log. */
अटल bool tpm_is_tpm2_log(व्योम *bios_event_log, u64 len)
अणु
	काष्ठा tcg_efi_specid_event_head *efispecid;
	काष्ठा tcg_pcr_event *event_header;
	पूर्णांक n;

	अगर (len < माप(*event_header))
		वापस false;
	len -= माप(*event_header);
	event_header = bios_event_log;

	अगर (len < माप(*efispecid))
		वापस false;
	efispecid = (काष्ठा tcg_efi_specid_event_head *)event_header->event;

	n = स_भेद(efispecid->signature, TCG_SPECID_SIG,
		   माप(TCG_SPECID_SIG));
	वापस n == 0;
पूर्ण

/* पढ़ो binary bios log */
पूर्णांक tpm_पढ़ो_log_acpi(काष्ठा tpm_chip *chip)
अणु
	काष्ठा acpi_tcpa *buff;
	acpi_status status;
	व्योम __iomem *virt;
	u64 len, start;
	काष्ठा tpm_bios_log *log;
	काष्ठा acpi_table_tpm2 *tbl;
	काष्ठा acpi_tpm2_phy *tpm2_phy;
	पूर्णांक क्रमmat;
	पूर्णांक ret;

	log = &chip->log;

	/* Unक्रमtuntely ACPI करोes not associate the event log with a specअगरic
	 * TPM, like PPI. Thus all ACPI TPMs will पढ़ो the same log.
	 */
	अगर (!chip->acpi_dev_handle)
		वापस -ENODEV;

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2) अणु
		status = acpi_get_table("TPM2", 1,
					(काष्ठा acpi_table_header **)&tbl);
		अगर (ACPI_FAILURE(status))
			वापस -ENODEV;

		अगर (tbl->header.length <
				माप(*tbl) + माप(काष्ठा acpi_tpm2_phy))
			वापस -ENODEV;

		tpm2_phy = (व्योम *)tbl + माप(*tbl);
		len = tpm2_phy->log_area_minimum_length;

		start = tpm2_phy->log_area_start_address;
		अगर (!start || !len)
			वापस -ENODEV;

		क्रमmat = EFI_TCG2_EVENT_LOG_FORMAT_TCG_2;
	पूर्ण अन्यथा अणु
		/* Find TCPA entry in RSDT (ACPI_LOGICAL_ADDRESSING) */
		status = acpi_get_table(ACPI_SIG_TCPA, 1,
					(काष्ठा acpi_table_header **)&buff);
		अगर (ACPI_FAILURE(status))
			वापस -ENODEV;

		चयन (buff->platक्रमm_class) अणु
		हाल BIOS_SERVER:
			len = buff->server.log_max_len;
			start = buff->server.log_start_addr;
			अवरोध;
		हाल BIOS_CLIENT:
		शेष:
			len = buff->client.log_max_len;
			start = buff->client.log_start_addr;
			अवरोध;
		पूर्ण

		क्रमmat = EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2;
	पूर्ण
	अगर (!len) अणु
		dev_warn(&chip->dev, "%s: TCPA log area empty\n", __func__);
		वापस -EIO;
	पूर्ण

	/* दो_स्मृति EventLog space */
	log->bios_event_log = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!log->bios_event_log)
		वापस -ENOMEM;

	log->bios_event_log_end = log->bios_event_log + len;

	ret = -EIO;
	virt = acpi_os_map_iomem(start, len);
	अगर (!virt)
		जाओ err;

	स_नकल_fromio(log->bios_event_log, virt, len);

	acpi_os_unmap_iomem(virt, len);

	अगर (chip->flags & TPM_CHIP_FLAG_TPM2 &&
	    !tpm_is_tpm2_log(log->bios_event_log, len)) अणु
		/* try EFI log next */
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	वापस क्रमmat;

err:
	kमुक्त(log->bios_event_log);
	log->bios_event_log = शून्य;
	वापस ret;

पूर्ण
