<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TPM_DEV_H
#घोषणा _TPM_DEV_H

#समावेश <linux/poll.h>
#समावेश "tpm.h"

काष्ठा file_priv अणु
	काष्ठा tpm_chip *chip;
	काष्ठा tpm_space *space;

	काष्ठा mutex buffer_mutex;
	काष्ठा समयr_list user_पढ़ो_समयr;      /* user needs to claim result */
	काष्ठा work_काष्ठा समयout_work;
	काष्ठा work_काष्ठा async_work;
	रुको_queue_head_t async_रुको;
	sमाप_प्रकार response_length;
	bool response_पढ़ो;
	bool command_enqueued;

	u8 data_buffer[TPM_बफ_मानE];
पूर्ण;

व्योम tpm_common_खोलो(काष्ठा file *file, काष्ठा tpm_chip *chip,
		     काष्ठा file_priv *priv, काष्ठा tpm_space *space);
sमाप_प्रकार tpm_common_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार size, loff_t *off);
sमाप_प्रकार tpm_common_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार size, loff_t *off);
__poll_t tpm_common_poll(काष्ठा file *file, poll_table *रुको);

व्योम tpm_common_release(काष्ठा file *file, काष्ठा file_priv *priv);
#पूर्ण_अगर
