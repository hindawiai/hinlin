<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HSI clients registration पूर्णांकerface
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 *
 * Contact: Carlos Chinea <carlos.chinea@nokia.com>
 */
#समावेश <linux/hsi/hsi.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश "hsi_core.h"

/*
 * hsi_board_list is only used पूर्णांकernally by the HSI framework.
 * No one अन्यथा is allowed to make use of it.
 */
LIST_HEAD(hsi_board_list);
EXPORT_SYMBOL_GPL(hsi_board_list);

/**
 * hsi_रेजिस्टर_board_info - Register HSI clients inक्रमmation
 * @info: Array of HSI clients on the board
 * @len: Length of the array
 *
 * HSI clients are अटलally declared and रेजिस्टरed on board files.
 *
 * HSI clients will be स्वतःmatically रेजिस्टरed to the HSI bus once the
 * controller and the port where the clients wishes to attach are रेजिस्टरed
 * to it.
 *
 * Return -त्रुटि_सं on failure, 0 on success.
 */
पूर्णांक __init hsi_रेजिस्टर_board_info(काष्ठा hsi_board_info स्थिर *info,
							अचिन्हित पूर्णांक len)
अणु
	काष्ठा hsi_cl_info *cl_info;

	cl_info = kसुस्मृति(len, माप(*cl_info), GFP_KERNEL);
	अगर (!cl_info)
		वापस -ENOMEM;

	क्रम (; len; len--, info++, cl_info++) अणु
		cl_info->info = *info;
		list_add_tail(&cl_info->list, &hsi_board_list);
	पूर्ण

	वापस 0;
पूर्ण
