<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _COMEDI_INTERNAL_H
#घोषणा _COMEDI_INTERNAL_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

/*
 * various पूर्णांकernal comedi stuff
 */

काष्ठा comedi_buf_map;
काष्ठा comedi_devconfig;
काष्ठा comedi_device;
काष्ठा comedi_insn;
काष्ठा comedi_rangeinfo;
काष्ठा comedi_subdevice;
काष्ठा device;

पूर्णांक करो_rangeinfo_ioctl(काष्ठा comedi_device *dev,
		       काष्ठा comedi_rangeinfo *it);
काष्ठा comedi_device *comedi_alloc_board_minor(काष्ठा device *hardware_device);
व्योम comedi_release_hardware_device(काष्ठा device *hardware_device);
पूर्णांक comedi_alloc_subdevice_minor(काष्ठा comedi_subdevice *s);
व्योम comedi_मुक्त_subdevice_minor(काष्ठा comedi_subdevice *s);

पूर्णांक comedi_buf_alloc(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		     अचिन्हित दीर्घ new_size);
व्योम comedi_buf_reset(काष्ठा comedi_subdevice *s);
bool comedi_buf_is_mmapped(काष्ठा comedi_subdevice *s);
व्योम comedi_buf_map_get(काष्ठा comedi_buf_map *bm);
पूर्णांक comedi_buf_map_put(काष्ठा comedi_buf_map *bm);
पूर्णांक comedi_buf_map_access(काष्ठा comedi_buf_map *bm, अचिन्हित दीर्घ offset,
			  व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो);
काष्ठा comedi_buf_map *
comedi_buf_map_from_subdev_get(काष्ठा comedi_subdevice *s);
अचिन्हित पूर्णांक comedi_buf_ग_लिखो_n_available(काष्ठा comedi_subdevice *s);
अचिन्हित पूर्णांक comedi_buf_ग_लिखो_n_allocated(काष्ठा comedi_subdevice *s);
व्योम comedi_device_cancel_all(काष्ठा comedi_device *dev);
bool comedi_can_स्वतः_मुक्त_spriv(काष्ठा comedi_subdevice *s);

बाह्य अचिन्हित पूर्णांक comedi_शेष_buf_size_kb;
बाह्य अचिन्हित पूर्णांक comedi_शेष_buf_maxsize_kb;

/* drivers.c */

बाह्य काष्ठा comedi_driver *comedi_drivers;
बाह्य काष्ठा mutex comedi_drivers_list_lock;

पूर्णांक insn_inval(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
	       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);

व्योम comedi_device_detach(काष्ठा comedi_device *dev);
पूर्णांक comedi_device_attach(काष्ठा comedi_device *dev,
			 काष्ठा comedi_devconfig *it);

#अगर_घोषित CONFIG_PROC_FS

/* proc.c */

व्योम comedi_proc_init(व्योम);
व्योम comedi_proc_cleanup(व्योम);
#अन्यथा
अटल अंतरभूत व्योम comedi_proc_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम comedi_proc_cleanup(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _COMEDI_INTERNAL_H */
