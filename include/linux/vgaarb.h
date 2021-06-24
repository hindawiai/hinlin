<शैली गुरु>
/*
 * The VGA aribiter manages VGA space routing and VGA resource decode to
 * allow multiple VGA devices to be used in a प्रणाली in a safe way.
 *
 * (C) Copyright 2005 Benjamin Herrenschmidt <benh@kernel.crashing.org>
 * (C) Copyright 2007 Paulo R. Zanoni <przanoni@gmail.com>
 * (C) Copyright 2007, 2009 Tiago Vignatti <vignatti@मुक्तdesktop.org>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS
 * IN THE SOFTWARE.
 *
 */

#अगर_अघोषित LINUX_VGA_H
#घोषणा LINUX_VGA_H

#समावेश <video/vga.h>

/* Legacy VGA regions */
#घोषणा VGA_RSRC_NONE	       0x00
#घोषणा VGA_RSRC_LEGACY_IO     0x01
#घोषणा VGA_RSRC_LEGACY_MEM    0x02
#घोषणा VGA_RSRC_LEGACY_MASK   (VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM)
/* Non-legacy access */
#घोषणा VGA_RSRC_NORMAL_IO     0x04
#घोषणा VGA_RSRC_NORMAL_MEM    0x08

/* Passing that instead of a pci_dev to use the प्रणाली "default"
 * device, that is the one used by vgacon. Archs will probably
 * have to provide their own vga_शेष_device();
 */
#घोषणा VGA_DEFAULT_DEVICE     (शून्य)

काष्ठा pci_dev;

/* For use by clients */

/**
 *     vga_set_legacy_decoding
 *
 *     @pdev: pci device of the VGA card
 *     @decodes: bit mask of what legacy regions the card decodes
 *
 *     Indicates to the arbiter अगर the card decodes legacy VGA IOs,
 *     legacy VGA Memory, both, or none. All cards शेष to both,
 *     the card driver (fbdev क्रम example) should tell the arbiter
 *     अगर it has disabled legacy decoding, so the card can be left
 *     out of the arbitration process (and can be safe to take
 *     पूर्णांकerrupts at any समय.
 */
#अगर defined(CONFIG_VGA_ARB)
बाह्य व्योम vga_set_legacy_decoding(काष्ठा pci_dev *pdev,
				    अचिन्हित पूर्णांक decodes);
#अन्यथा
अटल अंतरभूत व्योम vga_set_legacy_decoding(काष्ठा pci_dev *pdev,
					   अचिन्हित पूर्णांक decodes) अणु पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_VGA_ARB)
बाह्य पूर्णांक vga_get(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक rsrc, पूर्णांक पूर्णांकerruptible);
#अन्यथा
अटल अंतरभूत पूर्णांक vga_get(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक rsrc, पूर्णांक पूर्णांकerruptible) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/**
 * vga_get_पूर्णांकerruptible
 * @pdev: pci device of the VGA card or शून्य क्रम the प्रणाली शेष
 * @rsrc: bit mask of resources to acquire and lock
 *
 * Shortcut to vga_get with पूर्णांकerruptible set to true.
 *
 * On success, release the VGA resource again with vga_put().
 */
अटल अंतरभूत पूर्णांक vga_get_पूर्णांकerruptible(काष्ठा pci_dev *pdev,
					अचिन्हित पूर्णांक rsrc)
अणु
       वापस vga_get(pdev, rsrc, 1);
पूर्ण

/**
 * vga_get_unपूर्णांकerruptible - लघुcut to vga_get()
 * @pdev: pci device of the VGA card or शून्य क्रम the प्रणाली शेष
 * @rsrc: bit mask of resources to acquire and lock
 *
 * Shortcut to vga_get with पूर्णांकerruptible set to false.
 *
 * On success, release the VGA resource again with vga_put().
 */
अटल अंतरभूत पूर्णांक vga_get_unपूर्णांकerruptible(काष्ठा pci_dev *pdev,
					  अचिन्हित पूर्णांक rsrc)
अणु
       वापस vga_get(pdev, rsrc, 0);
पूर्ण

#अगर defined(CONFIG_VGA_ARB)
बाह्य व्योम vga_put(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक rsrc);
#अन्यथा
अटल अंतरभूत व्योम vga_put(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक rsrc)
अणु
पूर्ण
#पूर्ण_अगर


#अगर_घोषित CONFIG_VGA_ARB
बाह्य काष्ठा pci_dev *vga_शेष_device(व्योम);
बाह्य व्योम vga_set_शेष_device(काष्ठा pci_dev *pdev);
बाह्य पूर्णांक vga_हटाओ_vgacon(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत काष्ठा pci_dev *vga_शेष_device(व्योम) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम vga_set_शेष_device(काष्ठा pci_dev *pdev) अणु पूर्ण
अटल अंतरभूत पूर्णांक vga_हटाओ_vgacon(काष्ठा pci_dev *pdev) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/*
 * Architectures should define this अगर they have several
 * independent PCI करोमुख्यs that can afक्रमd concurrent VGA
 * decoding
 */
#अगर_अघोषित __ARCH_HAS_VGA_CONFLICT
अटल अंतरभूत पूर्णांक vga_conflicts(काष्ठा pci_dev *p1, काष्ठा pci_dev *p2)
अणु
       वापस 1;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_VGA_ARB)
पूर्णांक vga_client_रेजिस्टर(काष्ठा pci_dev *pdev, व्योम *cookie,
			व्योम (*irq_set_state)(व्योम *cookie, bool state),
			अचिन्हित पूर्णांक (*set_vga_decode)(व्योम *cookie, bool state));
#अन्यथा
अटल अंतरभूत पूर्णांक vga_client_रेजिस्टर(काष्ठा pci_dev *pdev, व्योम *cookie,
				      व्योम (*irq_set_state)(व्योम *cookie, bool state),
				      अचिन्हित पूर्णांक (*set_vga_decode)(व्योम *cookie, bool state))
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* LINUX_VGA_H */
