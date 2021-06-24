<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SH_SETUP_H
#घोषणा _SH_SETUP_H

#समावेश <uapi/यंत्र/setup.h>

/*
 * This is set up by the setup-routine at boot-समय
 */
#घोषणा PARAM	((अचिन्हित अक्षर *)empty_zero_page)

#घोषणा MOUNT_ROOT_RDONLY (*(अचिन्हित दीर्घ *) (PARAM+0x000))
#घोषणा RAMDISK_FLAGS (*(अचिन्हित दीर्घ *) (PARAM+0x004))
#घोषणा ORIG_ROOT_DEV (*(अचिन्हित दीर्घ *) (PARAM+0x008))
#घोषणा LOADER_TYPE (*(अचिन्हित दीर्घ *) (PARAM+0x00c))
#घोषणा INITRD_START (*(अचिन्हित दीर्घ *) (PARAM+0x010))
#घोषणा INITRD_SIZE (*(अचिन्हित दीर्घ *) (PARAM+0x014))
/* ... */
#घोषणा COMMAND_LINE ((अक्षर *) (PARAM+0x100))

व्योम sh_mv_setup(व्योम);
व्योम check_क्रम_initrd(व्योम);
व्योम per_cpu_trap_init(व्योम);

#पूर्ण_अगर /* _SH_SETUP_H */
