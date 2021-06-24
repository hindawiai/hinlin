<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (c) 2012-2015 Qualcomm Atheros, Inc. */

#समावेश <linux/types.h>

#घोषणा PCM_DATA_INVALID_DW_VAL (0xB0BA0000)

व्योम wil_pmc_init(काष्ठा wil6210_priv *wil);
व्योम wil_pmc_alloc(काष्ठा wil6210_priv *wil,
		   पूर्णांक num_descriptors, पूर्णांक descriptor_size);
व्योम wil_pmc_मुक्त(काष्ठा wil6210_priv *wil, पूर्णांक send_pmc_cmd);
पूर्णांक wil_pmc_last_cmd_status(काष्ठा wil6210_priv *wil);
sमाप_प्रकार wil_pmc_पढ़ो(काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
loff_t wil_pmc_llseek(काष्ठा file *filp, loff_t off, पूर्णांक whence);
पूर्णांक wil_pmcring_पढ़ो(काष्ठा seq_file *s, व्योम *data);
