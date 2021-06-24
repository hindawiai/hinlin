<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
  nubus.h: various definitions and prototypes क्रम NuBus drivers to use.

  Originally written by Alan Cox.

  Hacked to death by C. Scott Ananian and David Huggins-Daines.
*/

#अगर_अघोषित LINUX_NUBUS_H
#घोषणा LINUX_NUBUS_H

#समावेश <linux/device.h>
#समावेश <यंत्र/nubus.h>
#समावेश <uapi/linux/nubus.h>

काष्ठा proc_dir_entry;
काष्ठा seq_file;

काष्ठा nubus_dir अणु
	अचिन्हित अक्षर *base;
	अचिन्हित अक्षर *ptr;
	पूर्णांक करोne;
	पूर्णांक mask;
	काष्ठा proc_dir_entry *procdir;
पूर्ण;

काष्ठा nubus_dirent अणु
	अचिन्हित अक्षर *base;
	अचिन्हित अक्षर type;
	__u32 data;	/* Actually 24 bits used */
	पूर्णांक mask;
पूर्ण;

काष्ठा nubus_board अणु
	काष्ठा device dev;

	/* Only 9-E actually exist, though 0-8 are also theoretically
	   possible, and 0 is a special हाल which represents the
	   motherboard and onboard peripherals (Ethernet, video) */
	पूर्णांक slot;
	/* For slot 0, this is bogus. */
	अक्षर name[64];

	/* Format block */
	अचिन्हित अक्षर *fblock;
	/* Root directory (करोes *not* always equal fblock + करोffset!) */
	अचिन्हित अक्षर *directory;

	अचिन्हित दीर्घ slot_addr;
	/* Offset to root directory (someबार) */
	अचिन्हित दीर्घ करोffset;
	/* Length over which to compute the crc */
	अचिन्हित दीर्घ rom_length;
	/* Completely useless most of the समय */
	अचिन्हित दीर्घ crc;
	अचिन्हित अक्षर rev;
	अचिन्हित अक्षर क्रमmat;
	अचिन्हित अक्षर lanes;

	/* Directory entry in /proc/bus/nubus */
	काष्ठा proc_dir_entry *procdir;
पूर्ण;

काष्ठा nubus_rsrc अणु
	काष्ठा list_head list;

	/* The functional resource ID */
	अचिन्हित अक्षर resid;
	/* These are mostly here क्रम convenience; we could always पढ़ो
	   them from the ROMs अगर we wanted to */
	अचिन्हित लघु category;
	अचिन्हित लघु type;
	अचिन्हित लघु dr_sw;
	अचिन्हित लघु dr_hw;

	/* Functional directory */
	अचिन्हित अक्षर *directory;
	/* Much of our info comes from here */
	काष्ठा nubus_board *board;
पूर्ण;

/* This is all NuBus functional resources (used to find devices later on) */
बाह्य काष्ठा list_head nubus_func_rsrcs;

काष्ठा nubus_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक (*probe)(काष्ठा nubus_board *board);
	पूर्णांक (*हटाओ)(काष्ठा nubus_board *board);
पूर्ण;

बाह्य काष्ठा bus_type nubus_bus_type;

/* Generic NuBus पूर्णांकerface functions, modelled after the PCI पूर्णांकerface */
#अगर_घोषित CONFIG_PROC_FS
व्योम nubus_proc_init(व्योम);
काष्ठा proc_dir_entry *nubus_proc_add_board(काष्ठा nubus_board *board);
काष्ठा proc_dir_entry *nubus_proc_add_rsrc_dir(काष्ठा proc_dir_entry *procdir,
					       स्थिर काष्ठा nubus_dirent *ent,
					       काष्ठा nubus_board *board);
व्योम nubus_proc_add_rsrc_mem(काष्ठा proc_dir_entry *procdir,
			     स्थिर काष्ठा nubus_dirent *ent,
			     अचिन्हित पूर्णांक size);
व्योम nubus_proc_add_rsrc(काष्ठा proc_dir_entry *procdir,
			 स्थिर काष्ठा nubus_dirent *ent);
#अन्यथा
अटल अंतरभूत व्योम nubus_proc_init(व्योम) अणुपूर्ण
अटल अंतरभूत
काष्ठा proc_dir_entry *nubus_proc_add_board(काष्ठा nubus_board *board)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत
काष्ठा proc_dir_entry *nubus_proc_add_rsrc_dir(काष्ठा proc_dir_entry *procdir,
					       स्थिर काष्ठा nubus_dirent *ent,
					       काष्ठा nubus_board *board)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम nubus_proc_add_rsrc_mem(काष्ठा proc_dir_entry *procdir,
					   स्थिर काष्ठा nubus_dirent *ent,
					   अचिन्हित पूर्णांक size) अणुपूर्ण
अटल अंतरभूत व्योम nubus_proc_add_rsrc(काष्ठा proc_dir_entry *procdir,
				       स्थिर काष्ठा nubus_dirent *ent) अणुपूर्ण
#पूर्ण_अगर

काष्ठा nubus_rsrc *nubus_first_rsrc_or_null(व्योम);
काष्ठा nubus_rsrc *nubus_next_rsrc_or_null(काष्ठा nubus_rsrc *from);

#घोषणा क्रम_each_func_rsrc(f) \
	क्रम (f = nubus_first_rsrc_or_null(); f; f = nubus_next_rsrc_or_null(f))

#घोषणा क्रम_each_board_func_rsrc(b, f) \
	क्रम_each_func_rsrc(f) अगर (f->board != b) अणुपूर्ण अन्यथा

/* These are somewhat more NuBus-specअगरic.  They all वापस 0 क्रम
   success and -1 क्रम failure, as you'd expect. */

/* The root directory which contains the board and functional
   directories */
पूर्णांक nubus_get_root_dir(स्थिर काष्ठा nubus_board *board,
		       काष्ठा nubus_dir *dir);
/* The board directory */
पूर्णांक nubus_get_board_dir(स्थिर काष्ठा nubus_board *board,
			काष्ठा nubus_dir *dir);
/* The functional directory */
पूर्णांक nubus_get_func_dir(स्थिर काष्ठा nubus_rsrc *fres, काष्ठा nubus_dir *dir);

/* These work on any directory gotten via the above */
पूर्णांक nubus_सूची_पढ़ो(काष्ठा nubus_dir *dir,
		  काष्ठा nubus_dirent *ent);
पूर्णांक nubus_find_rsrc(काष्ठा nubus_dir *dir,
		    अचिन्हित अक्षर rsrc_type,
		    काष्ठा nubus_dirent *ent);
पूर्णांक nubus_सूची_शुरु(काष्ठा nubus_dir *dir);

/* Things to करो with directory entries */
पूर्णांक nubus_get_subdir(स्थिर काष्ठा nubus_dirent *ent,
		     काष्ठा nubus_dir *dir);
व्योम nubus_get_rsrc_mem(व्योम *dest, स्थिर काष्ठा nubus_dirent *dirent,
			अचिन्हित पूर्णांक len);
अचिन्हित पूर्णांक nubus_get_rsrc_str(अक्षर *dest, स्थिर काष्ठा nubus_dirent *dirent,
				अचिन्हित पूर्णांक len);
व्योम nubus_seq_ग_लिखो_rsrc_mem(काष्ठा seq_file *m,
			      स्थिर काष्ठा nubus_dirent *dirent,
			      अचिन्हित पूर्णांक len);
अचिन्हित अक्षर *nubus_dirptr(स्थिर काष्ठा nubus_dirent *nd);

/* Declarations relating to driver model objects */
पूर्णांक nubus_parent_device_रेजिस्टर(व्योम);
पूर्णांक nubus_device_रेजिस्टर(काष्ठा nubus_board *board);
पूर्णांक nubus_driver_रेजिस्टर(काष्ठा nubus_driver *ndrv);
व्योम nubus_driver_unरेजिस्टर(काष्ठा nubus_driver *ndrv);
पूर्णांक nubus_proc_show(काष्ठा seq_file *m, व्योम *data);

अटल अंतरभूत व्योम nubus_set_drvdata(काष्ठा nubus_board *board, व्योम *data)
अणु
	dev_set_drvdata(&board->dev, data);
पूर्ण

अटल अंतरभूत व्योम *nubus_get_drvdata(काष्ठा nubus_board *board)
अणु
	वापस dev_get_drvdata(&board->dev);
पूर्ण

/* Returns a poपूर्णांकer to the "standard" slot space. */
अटल अंतरभूत व्योम *nubus_slot_addr(पूर्णांक slot)
अणु
	वापस (व्योम *)(0xF0000000 | (slot << 24));
पूर्ण

#पूर्ण_अगर /* LINUX_NUBUS_H */
