<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Functions to handle diagnostics.
 *
 * Copyright IBM Corp. 2018
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश "zfcp_diag.h"
#समावेश "zfcp_ext.h"
#समावेश "zfcp_def.h"

अटल DECLARE_WAIT_QUEUE_HEAD(__zfcp_diag_publish_रुको);

/**
 * zfcp_diag_adapter_setup() - Setup storage क्रम adapter diagnostics.
 * @adapter: the adapter to setup diagnostics क्रम.
 *
 * Creates the data-काष्ठाures to store the diagnostics क्रम an adapter. This
 * overग_लिखोs whatever was stored beक्रमe at &zfcp_adapter->diagnostics!
 *
 * Return:
 * * 0	     - Everyting is OK
 * * -ENOMEM - Could not allocate all/parts of the data-काष्ठाures;
 *	       &zfcp_adapter->diagnostics reमुख्यs unchanged
 */
पूर्णांक zfcp_diag_adapter_setup(काष्ठा zfcp_adapter *स्थिर adapter)
अणु
	काष्ठा zfcp_diag_adapter *diag;
	काष्ठा zfcp_diag_header *hdr;

	diag = kzalloc(माप(*diag), GFP_KERNEL);
	अगर (diag == शून्य)
		वापस -ENOMEM;

	diag->max_age = (5 * 1000); /* शेष value: 5 s */

	/* setup header क्रम port_data */
	hdr = &diag->port_data.header;

	spin_lock_init(&hdr->access_lock);
	hdr->buffer = &diag->port_data.data;
	hdr->buffer_size = माप(diag->port_data.data);
	/* set the बारtamp so that the first test on age will always fail */
	hdr->बारtamp = jअगरfies - msecs_to_jअगरfies(diag->max_age);

	/* setup header क्रम config_data */
	hdr = &diag->config_data.header;

	spin_lock_init(&hdr->access_lock);
	hdr->buffer = &diag->config_data.data;
	hdr->buffer_size = माप(diag->config_data.data);
	/* set the बारtamp so that the first test on age will always fail */
	hdr->बारtamp = jअगरfies - msecs_to_jअगरfies(diag->max_age);

	adapter->diagnostics = diag;
	वापस 0;
पूर्ण

/**
 * zfcp_diag_adapter_मुक्त() - Frees all adapter diagnostics allocations.
 * @adapter: the adapter whose diagnostic काष्ठाures should be मुक्तd.
 *
 * Frees all data-काष्ठाures in the given adapter that store diagnostics
 * inक्रमmation. Can savely be called with partially setup diagnostics.
 */
व्योम zfcp_diag_adapter_मुक्त(काष्ठा zfcp_adapter *स्थिर adapter)
अणु
	kमुक्त(adapter->diagnostics);
	adapter->diagnostics = शून्य;
पूर्ण

/**
 * zfcp_diag_update_xdata() - Update a diagnostics buffer.
 * @hdr: the meta data to update.
 * @data: data to use क्रम the update.
 * @incomplete: flag stating whether the data in @data is incomplete.
 */
व्योम zfcp_diag_update_xdata(काष्ठा zfcp_diag_header *स्थिर hdr,
			    स्थिर व्योम *स्थिर data, स्थिर bool incomplete)
अणु
	स्थिर अचिन्हित दीर्घ capture_बारtamp = jअगरfies;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hdr->access_lock, flags);

	/* make sure we never go पूर्णांकo the past with an update */
	अगर (!समय_after_eq(capture_बारtamp, hdr->बारtamp))
		जाओ out;

	hdr->बारtamp = capture_बारtamp;
	hdr->incomplete = incomplete;
	स_नकल(hdr->buffer, data, hdr->buffer_size);
out:
	spin_unlock_irqrestore(&hdr->access_lock, flags);
पूर्ण

/**
 * zfcp_diag_update_port_data_buffer() - Implementation of
 *					 &प्रकार zfcp_diag_update_buffer_func
 *					 to collect and update Port Data.
 * @adapter: Adapter to collect Port Data from.
 *
 * This call is SYNCHRONOUS ! It blocks till the respective command has
 * finished completely, or has failed in some way.
 *
 * Return:
 * * 0		- Successfully retrieved new Diagnostics and Updated the buffer;
 *		  this also includes हालs where data was retrieved, but
 *		  incomplete; you'll have to check the flag ``incomplete``
 *		  of &काष्ठा zfcp_diag_header.
 * * see zfcp_fsf_exchange_port_data_sync() क्रम possible error-codes (
 *   excluding -EAGAIN)
 */
पूर्णांक zfcp_diag_update_port_data_buffer(काष्ठा zfcp_adapter *स्थिर adapter)
अणु
	पूर्णांक rc;

	rc = zfcp_fsf_exchange_port_data_sync(adapter->qdio, शून्य);
	अगर (rc == -EAGAIN)
		rc = 0; /* संकेतing incomplete via काष्ठा zfcp_diag_header */

	/* buffer-data was updated in zfcp_fsf_exchange_port_data_handler() */

	वापस rc;
पूर्ण

/**
 * zfcp_diag_update_config_data_buffer() - Implementation of
 *					   &प्रकार zfcp_diag_update_buffer_func
 *					   to collect and update Config Data.
 * @adapter: Adapter to collect Config Data from.
 *
 * This call is SYNCHRONOUS ! It blocks till the respective command has
 * finished completely, or has failed in some way.
 *
 * Return:
 * * 0		- Successfully retrieved new Diagnostics and Updated the buffer;
 *		  this also includes हालs where data was retrieved, but
 *		  incomplete; you'll have to check the flag ``incomplete``
 *		  of &काष्ठा zfcp_diag_header.
 * * see zfcp_fsf_exchange_config_data_sync() क्रम possible error-codes (
 *   excluding -EAGAIN)
 */
पूर्णांक zfcp_diag_update_config_data_buffer(काष्ठा zfcp_adapter *स्थिर adapter)
अणु
	पूर्णांक rc;

	rc = zfcp_fsf_exchange_config_data_sync(adapter->qdio, शून्य);
	अगर (rc == -EAGAIN)
		rc = 0; /* संकेतing incomplete via काष्ठा zfcp_diag_header */

	/* buffer-data was updated in zfcp_fsf_exchange_config_data_handler() */

	वापस rc;
पूर्ण

अटल पूर्णांक __zfcp_diag_update_buffer(काष्ठा zfcp_adapter *स्थिर adapter,
				     काष्ठा zfcp_diag_header *स्थिर hdr,
				     zfcp_diag_update_buffer_func buffer_update,
				     अचिन्हित दीर्घ *स्थिर flags)
	__must_hold(hdr->access_lock)
अणु
	पूर्णांक rc;

	अगर (hdr->updating == 1) अणु
		rc = रुको_event_पूर्णांकerruptible_lock_irq(__zfcp_diag_publish_रुको,
						       hdr->updating == 0,
						       hdr->access_lock);
		rc = (rc == 0 ? -EAGAIN : -EINTR);
	पूर्ण अन्यथा अणु
		hdr->updating = 1;
		spin_unlock_irqrestore(&hdr->access_lock, *flags);

		/* unlocked, because update function sleeps */
		rc = buffer_update(adapter);

		spin_lock_irqsave(&hdr->access_lock, *flags);
		hdr->updating = 0;

		/*
		 * every thपढ़ो रुकोing here went via an पूर्णांकerruptible रुको,
		 * so its fine to only wake those
		 */
		wake_up_पूर्णांकerruptible_all(&__zfcp_diag_publish_रुको);
	पूर्ण

	वापस rc;
पूर्ण

अटल bool
__zfcp_diag_test_buffer_age_isfresh(स्थिर काष्ठा zfcp_diag_adapter *स्थिर diag,
				    स्थिर काष्ठा zfcp_diag_header *स्थिर hdr)
	__must_hold(hdr->access_lock)
अणु
	स्थिर अचिन्हित दीर्घ now = jअगरfies;

	/*
	 * Should not happen (data is from the future).. अगर it करोes, still
	 * संकेत that it needs refresh
	 */
	अगर (!समय_after_eq(now, hdr->बारtamp))
		वापस false;

	अगर (jअगरfies_to_msecs(now - hdr->बारtamp) >= diag->max_age)
		वापस false;

	वापस true;
पूर्ण

/**
 * zfcp_diag_update_buffer_limited() - Collect diagnostics and update a
 *				       diagnostics buffer rate limited.
 * @adapter: Adapter to collect the diagnostics from.
 * @hdr: buffer-header क्रम which to update with the collected diagnostics.
 * @buffer_update: Specअगरic implementation क्रम collecting and updating.
 *
 * This function will cause an update of the given @hdr by calling the also
 * given @buffer_update function. If called by multiple sources at the same
 * समय, it will synchornize the update by only allowing one source to call
 * @buffer_update and the others to रुको क्रम that source to complete instead
 * (the रुको is पूर्णांकerruptible).
 *
 * Additionally this version is rate-limited and will only निकास अगर either the
 * buffer is fresh enough (within the limit) - it will करो nothing अगर the buffer
 * is fresh enough to begin with -, or अगर the source/thपढ़ो that started this
 * update is the one that made the update (to prevent endless loops).
 *
 * Return:
 * * 0		- If the update was successfully published and/or the buffer is
 *		  fresh enough
 * * -EINTR	- If the thपढ़ो went पूर्णांकo the रुको-state and was पूर्णांकerrupted
 * * whatever @buffer_update वापसs
 */
पूर्णांक zfcp_diag_update_buffer_limited(काष्ठा zfcp_adapter *स्थिर adapter,
				    काष्ठा zfcp_diag_header *स्थिर hdr,
				    zfcp_diag_update_buffer_func buffer_update)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&hdr->access_lock, flags);

	क्रम (rc = 0;
	     !__zfcp_diag_test_buffer_age_isfresh(adapter->diagnostics, hdr);
	     rc = 0) अणु
		rc = __zfcp_diag_update_buffer(adapter, hdr, buffer_update,
					       &flags);
		अगर (rc != -EAGAIN)
			अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&hdr->access_lock, flags);

	वापस rc;
पूर्ण
