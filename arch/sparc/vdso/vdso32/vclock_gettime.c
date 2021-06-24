<शैली गुरु>
/*
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
 */

#घोषणा	BUILD_VDSO32

#अगर_घोषित	CONFIG_SPARC64

/*
 * in हाल of a 32 bit VDSO क्रम a 64 bit kernel fake a 32 bit kernel
 * configuration
 */
#अघोषित	CONFIG_64BIT
#अघोषित	CONFIG_SPARC64
#घोषणा	BUILD_VDSO32_64
#घोषणा	CONFIG_32BIT
#अघोषित	CONFIG_QUEUED_RWLOCKS
#अघोषित	CONFIG_QUEUED_SPINLOCKS

#पूर्ण_अगर

#समावेश "../vclock_gettime.c"
