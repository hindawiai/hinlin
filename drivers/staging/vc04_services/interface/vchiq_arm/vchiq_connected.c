<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2010-2012 Broadcom. All rights reserved. */

#समावेश "vchiq_connected.h"
#समावेश "vchiq_core.h"
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#घोषणा  MAX_CALLBACKS  10

अटल   पूर्णांक                        g_connected;
अटल   पूर्णांक                        g_num_deferred_callbacks;
अटल   VCHIQ_CONNECTED_CALLBACK_T g_deferred_callback[MAX_CALLBACKS];
अटल   पूर्णांक                        g_once_init;
अटल   DEFINE_MUTEX(g_connected_mutex);

/* Function to initialize our lock */
अटल व्योम connected_init(व्योम)
अणु
	अगर (!g_once_init) अणु
		g_once_init = 1;
	पूर्ण
पूर्ण

/*
 * This function is used to defer initialization until the vchiq stack is
 * initialized. If the stack is alपढ़ोy initialized, then the callback will
 * be made immediately, otherwise it will be deferred until
 * vchiq_call_connected_callbacks is called.
 */
व्योम vchiq_add_connected_callback(VCHIQ_CONNECTED_CALLBACK_T callback)
अणु
	connected_init();

	अगर (mutex_lock_समाप्तable(&g_connected_mutex))
		वापस;

	अगर (g_connected)
		/* We're alपढ़ोy connected. Call the callback immediately. */

		callback();
	अन्यथा अणु
		अगर (g_num_deferred_callbacks >= MAX_CALLBACKS)
			vchiq_log_error(vchiq_core_log_level,
				"There already %d callback registered - please increase MAX_CALLBACKS",
				g_num_deferred_callbacks);
		अन्यथा अणु
			g_deferred_callback[g_num_deferred_callbacks] =
				callback;
			g_num_deferred_callbacks++;
		पूर्ण
	पूर्ण
	mutex_unlock(&g_connected_mutex);
पूर्ण

/*
 * This function is called by the vchiq stack once it has been connected to
 * the videocore and clients can start to use the stack.
 */
व्योम vchiq_call_connected_callbacks(व्योम)
अणु
	पूर्णांक i;

	connected_init();

	अगर (mutex_lock_समाप्तable(&g_connected_mutex))
		वापस;

	क्रम (i = 0; i <  g_num_deferred_callbacks; i++)
		g_deferred_callback[i]();

	g_num_deferred_callbacks = 0;
	g_connected = 1;
	mutex_unlock(&g_connected_mutex);
पूर्ण
EXPORT_SYMBOL(vchiq_add_connected_callback);
