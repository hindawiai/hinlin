<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * zfcp device driver
 *
 * Definitions क्रम handling diagnostics in the the zfcp device driver.
 *
 * Copyright IBM Corp. 2018, 2020
 */

#अगर_अघोषित ZFCP_DIAG_H
#घोषणा ZFCP_DIAG_H

#समावेश <linux/spinlock.h>

#समावेश "zfcp_fsf.h"
#समावेश "zfcp_def.h"

/**
 * काष्ठा zfcp_diag_header - general part of a diagnostic buffer.
 * @access_lock: lock protecting all the data in this buffer.
 * @updating: flag showing that an update क्रम this buffer is currently running.
 * @incomplete: flag showing that the data in @buffer is incomplete.
 * @बारtamp: समय in jअगरfies when the data of this buffer was last captured.
 * @buffer: implementation-depending data of this buffer
 * @buffer_size: size of @buffer
 */
काष्ठा zfcp_diag_header अणु
	spinlock_t	access_lock;

	/* Flags */
	u64		updating	:1;
	u64		incomplete	:1;

	अचिन्हित दीर्घ	बारtamp;

	व्योम		*buffer;
	माप_प्रकार		buffer_size;
पूर्ण;

/**
 * काष्ठा zfcp_diag_adapter - central storage क्रम all diagnostics concerning an
 *			      adapter.
 * @max_age: maximum age of data in diagnostic buffers beक्रमe they need to be
 *	     refreshed (in ms).
 * @port_data: data retrieved using exchange port data.
 * @port_data.header: header with metadata क्रम the cache in @port_data.data.
 * @port_data.data: cached QTCB Bottom of command exchange port data.
 * @config_data: data retrieved using exchange config data.
 * @config_data.header: header with metadata क्रम the cache in @config_data.data.
 * @config_data.data: cached QTCB Bottom of command exchange config data.
 */
काष्ठा zfcp_diag_adapter अणु
	अचिन्हित दीर्घ	max_age;

	काष्ठा zfcp_diag_adapter_port_data अणु
		काष्ठा zfcp_diag_header		header;
		काष्ठा fsf_qtcb_bottom_port	data;
	पूर्ण port_data;
	काष्ठा zfcp_diag_adapter_config_data अणु
		काष्ठा zfcp_diag_header		header;
		काष्ठा fsf_qtcb_bottom_config	data;
	पूर्ण config_data;
पूर्ण;

पूर्णांक zfcp_diag_adapter_setup(काष्ठा zfcp_adapter *स्थिर adapter);
व्योम zfcp_diag_adapter_मुक्त(काष्ठा zfcp_adapter *स्थिर adapter);

व्योम zfcp_diag_update_xdata(काष्ठा zfcp_diag_header *स्थिर hdr,
			    स्थिर व्योम *स्थिर data, स्थिर bool incomplete);

/*
 * Function-Type used in zfcp_diag_update_buffer_limited() क्रम the function
 * that करोes the buffer-implementation dependent work.
 */
प्रकार पूर्णांक (*zfcp_diag_update_buffer_func)(काष्ठा zfcp_adapter *स्थिर adapter);

पूर्णांक zfcp_diag_update_config_data_buffer(काष्ठा zfcp_adapter *स्थिर adapter);
पूर्णांक zfcp_diag_update_port_data_buffer(काष्ठा zfcp_adapter *स्थिर adapter);
पूर्णांक zfcp_diag_update_buffer_limited(काष्ठा zfcp_adapter *स्थिर adapter,
				    काष्ठा zfcp_diag_header *स्थिर hdr,
				    zfcp_diag_update_buffer_func buffer_update);

/**
 * zfcp_diag_support_sfp() - Return %true अगर the @adapter supports reporting
 *			     SFP Data.
 * @adapter: adapter to test the availability of SFP Data reporting क्रम.
 */
अटल अंतरभूत bool
zfcp_diag_support_sfp(स्थिर काष्ठा zfcp_adapter *स्थिर adapter)
अणु
	वापस !!(adapter->adapter_features & FSF_FEATURE_REPORT_SFP_DATA);
पूर्ण

#पूर्ण_अगर /* ZFCP_DIAG_H */
