<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NOUVEAU_ACPI_H__
#घोषणा __NOUVEAU_ACPI_H__

#घोषणा ROM_BIOS_PAGE 4096

#अगर defined(CONFIG_ACPI) && defined(CONFIG_X86)
bool nouveau_is_optimus(व्योम);
bool nouveau_is_v1_dsm(व्योम);
व्योम nouveau_रेजिस्टर_dsm_handler(व्योम);
व्योम nouveau_unरेजिस्टर_dsm_handler(व्योम);
व्योम nouveau_चयनeroo_optimus_dsm(व्योम);
व्योम *nouveau_acpi_edid(काष्ठा drm_device *, काष्ठा drm_connector *);
#अन्यथा
अटल अंतरभूत bool nouveau_is_optimus(व्योम) अणु वापस false; पूर्ण;
अटल अंतरभूत bool nouveau_is_v1_dsm(व्योम) अणु वापस false; पूर्ण;
अटल अंतरभूत व्योम nouveau_रेजिस्टर_dsm_handler(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम nouveau_unरेजिस्टर_dsm_handler(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम nouveau_चयनeroo_optimus_dsm(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम *nouveau_acpi_edid(काष्ठा drm_device *dev, काष्ठा drm_connector *connector) अणु वापस शून्य; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
