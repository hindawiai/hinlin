<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __REBOOT_MODE_H__
#घोषणा __REBOOT_MODE_H__

काष्ठा reboot_mode_driver अणु
	काष्ठा device *dev;
	काष्ठा list_head head;
	पूर्णांक (*ग_लिखो)(काष्ठा reboot_mode_driver *reboot, अचिन्हित पूर्णांक magic);
	काष्ठा notअगरier_block reboot_notअगरier;
पूर्ण;

पूर्णांक reboot_mode_रेजिस्टर(काष्ठा reboot_mode_driver *reboot);
पूर्णांक reboot_mode_unरेजिस्टर(काष्ठा reboot_mode_driver *reboot);
पूर्णांक devm_reboot_mode_रेजिस्टर(काष्ठा device *dev,
			      काष्ठा reboot_mode_driver *reboot);
व्योम devm_reboot_mode_unरेजिस्टर(काष्ठा device *dev,
				 काष्ठा reboot_mode_driver *reboot);

#पूर्ण_अगर
