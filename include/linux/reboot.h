<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_REBOOT_H
#घोषणा _LINUX_REBOOT_H


#समावेश <linux/notअगरier.h>
#समावेश <uapi/linux/reboot.h>

काष्ठा device;

#घोषणा SYS_DOWN	0x0001	/* Notअगरy of प्रणाली करोwn */
#घोषणा SYS_RESTART	SYS_DOWN
#घोषणा SYS_HALT	0x0002	/* Notअगरy of प्रणाली halt */
#घोषणा SYS_POWER_OFF	0x0003	/* Notअगरy of प्रणाली घातer off */

क्रमागत reboot_mode अणु
	REBOOT_UNDEFINED = -1,
	REBOOT_COLD = 0,
	REBOOT_WARM,
	REBOOT_HARD,
	REBOOT_SOFT,
	REBOOT_GPIO,
पूर्ण;
बाह्य क्रमागत reboot_mode reboot_mode;
बाह्य क्रमागत reboot_mode panic_reboot_mode;

क्रमागत reboot_type अणु
	BOOT_TRIPLE	= 't',
	BOOT_KBD	= 'k',
	BOOT_BIOS	= 'b',
	BOOT_ACPI	= 'a',
	BOOT_EFI	= 'e',
	BOOT_CF9_FORCE	= 'p',
	BOOT_CF9_SAFE	= 'q',
पूर्ण;
बाह्य क्रमागत reboot_type reboot_type;

बाह्य पूर्णांक reboot_शेष;
बाह्य पूर्णांक reboot_cpu;
बाह्य पूर्णांक reboot_क्रमce;


बाह्य पूर्णांक रेजिस्टर_reboot_notअगरier(काष्ठा notअगरier_block *);
बाह्य पूर्णांक unरेजिस्टर_reboot_notअगरier(काष्ठा notअगरier_block *);

बाह्य पूर्णांक devm_रेजिस्टर_reboot_notअगरier(काष्ठा device *, काष्ठा notअगरier_block *);

बाह्य पूर्णांक रेजिस्टर_restart_handler(काष्ठा notअगरier_block *);
बाह्य पूर्णांक unरेजिस्टर_restart_handler(काष्ठा notअगरier_block *);
बाह्य व्योम करो_kernel_restart(अक्षर *cmd);

/*
 * Architecture-specअगरic implementations of sys_reboot commands.
 */

बाह्य व्योम migrate_to_reboot_cpu(व्योम);
बाह्य व्योम machine_restart(अक्षर *cmd);
बाह्य व्योम machine_halt(व्योम);
बाह्य व्योम machine_घातer_off(व्योम);

बाह्य व्योम machine_shutकरोwn(व्योम);
काष्ठा pt_regs;
बाह्य व्योम machine_crash_shutकरोwn(काष्ठा pt_regs *);

/*
 * Architecture independent implemenations of sys_reboot commands.
 */

बाह्य व्योम kernel_restart_prepare(अक्षर *cmd);
बाह्य व्योम kernel_restart(अक्षर *cmd);
बाह्य व्योम kernel_halt(व्योम);
बाह्य व्योम kernel_घातer_off(व्योम);

बाह्य पूर्णांक C_A_D; /* क्रम sysctl */
व्योम ctrl_alt_del(व्योम);

#घोषणा POWEROFF_CMD_PATH_LEN	256
बाह्य अक्षर घातeroff_cmd[POWEROFF_CMD_PATH_LEN];

बाह्य व्योम orderly_घातeroff(bool क्रमce);
बाह्य व्योम orderly_reboot(व्योम);

/*
 * Emergency restart, callable from an पूर्णांकerrupt handler.
 */

बाह्य व्योम emergency_restart(व्योम);
#समावेश <यंत्र/emergency-restart.h>

#पूर्ण_अगर /* _LINUX_REBOOT_H */
