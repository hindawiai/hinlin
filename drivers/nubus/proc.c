<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* drivers/nubus/proc.c: Proc FS पूर्णांकerface क्रम NuBus.

   By David Huggins-Daines <dhd@debian.org>

   Much code and many ideas from drivers/pci/proc.c:
   Copyright (c) 1997, 1998 Martin Mares <mj@atrey.karlin.mff.cuni.cz>

   This is initially based on the Zorro and PCI पूर्णांकerfaces.  However,
   it works somewhat dअगरferently.  The पूर्णांकent is to provide a
   काष्ठाure in /proc analogous to the काष्ठाure of the NuBus ROM
   resources.

   Thereक्रमe each board function माला_लो a directory, which may in turn
   contain subdirectories.  Each slot resource is a file.  Unrecognized
   resources are empty files, since every resource ID requires a special
   हाल (e.g. अगर the resource ID implies a directory or block, then its
   value has to be पूर्णांकerpreted as a slot ROM poपूर्णांकer etc.).
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/nubus.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>

/*
 * /proc/bus/nubus/devices stuff
 */

अटल पूर्णांक
nubus_devices_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा nubus_rsrc *fres;

	क्रम_each_func_rsrc(fres)
		seq_म_लिखो(m, "%x\t%04x %04x %04x %04x\t%08lx\n",
			   fres->board->slot, fres->category, fres->type,
			   fres->dr_sw, fres->dr_hw, fres->board->slot_addr);
	वापस 0;
पूर्ण

अटल काष्ठा proc_dir_entry *proc_bus_nubus_dir;

/*
 * /proc/bus/nubus/x/ stuff
 */

काष्ठा proc_dir_entry *nubus_proc_add_board(काष्ठा nubus_board *board)
अणु
	अक्षर name[2];

	अगर (!proc_bus_nubus_dir)
		वापस शून्य;
	snम_लिखो(name, माप(name), "%x", board->slot);
	वापस proc_सूची_गढ़ो(name, proc_bus_nubus_dir);
पूर्ण

/* The PDE निजी data क्रम any directory under /proc/bus/nubus/x/
 * is the bytelanes value क्रम the board in slot x.
 */

काष्ठा proc_dir_entry *nubus_proc_add_rsrc_dir(काष्ठा proc_dir_entry *procdir,
					       स्थिर काष्ठा nubus_dirent *ent,
					       काष्ठा nubus_board *board)
अणु
	अक्षर name[9];
	पूर्णांक lanes = board->lanes;

	अगर (!procdir)
		वापस शून्य;
	snम_लिखो(name, माप(name), "%x", ent->type);
	वापस proc_सूची_गढ़ो_data(name, 0555, procdir, (व्योम *)lanes);
पूर्ण

/* The PDE निजी data क्रम a file under /proc/bus/nubus/x/ is a poपूर्णांकer to
 * an instance of the following काष्ठाure, which gives the location and size
 * of the resource data in the slot ROM. For slot resources which hold only a
 * small पूर्णांकeger, this पूर्णांकeger value is stored directly and size is set to 0.
 * A शून्य निजी data poपूर्णांकer indicates an unrecognized resource.
 */

काष्ठा nubus_proc_pde_data अणु
	अचिन्हित अक्षर *res_ptr;
	अचिन्हित पूर्णांक res_size;
पूर्ण;

अटल काष्ठा nubus_proc_pde_data *
nubus_proc_alloc_pde_data(अचिन्हित अक्षर *ptr, अचिन्हित पूर्णांक size)
अणु
	काष्ठा nubus_proc_pde_data *pde_data;

	pde_data = kदो_स्मृति(माप(*pde_data), GFP_KERNEL);
	अगर (!pde_data)
		वापस शून्य;

	pde_data->res_ptr = ptr;
	pde_data->res_size = size;
	वापस pde_data;
पूर्ण

अटल पूर्णांक nubus_proc_rsrc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा inode *inode = m->निजी;
	काष्ठा nubus_proc_pde_data *pde_data;

	pde_data = PDE_DATA(inode);
	अगर (!pde_data)
		वापस 0;

	अगर (pde_data->res_size > m->size)
		वापस -EFBIG;

	अगर (pde_data->res_size) अणु
		पूर्णांक lanes = (पूर्णांक)proc_get_parent_data(inode);
		काष्ठा nubus_dirent ent;

		अगर (!lanes)
			वापस 0;

		ent.mask = lanes;
		ent.base = pde_data->res_ptr;
		ent.data = 0;
		nubus_seq_ग_लिखो_rsrc_mem(m, &ent, pde_data->res_size);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक data = (अचिन्हित पूर्णांक)pde_data->res_ptr;

		seq_अ_दो(m, data >> 16);
		seq_अ_दो(m, data >> 8);
		seq_अ_दो(m, data >> 0);
	पूर्ण
	वापस 0;
पूर्ण

व्योम nubus_proc_add_rsrc_mem(काष्ठा proc_dir_entry *procdir,
			     स्थिर काष्ठा nubus_dirent *ent,
			     अचिन्हित पूर्णांक size)
अणु
	अक्षर name[9];
	काष्ठा nubus_proc_pde_data *pde_data;

	अगर (!procdir)
		वापस;

	snम_लिखो(name, माप(name), "%x", ent->type);
	अगर (size)
		pde_data = nubus_proc_alloc_pde_data(nubus_dirptr(ent), size);
	अन्यथा
		pde_data = शून्य;
	proc_create_single_data(name, S_IFREG | 0444, procdir,
			nubus_proc_rsrc_show, pde_data);
पूर्ण

व्योम nubus_proc_add_rsrc(काष्ठा proc_dir_entry *procdir,
			 स्थिर काष्ठा nubus_dirent *ent)
अणु
	अक्षर name[9];
	अचिन्हित अक्षर *data = (अचिन्हित अक्षर *)ent->data;

	अगर (!procdir)
		वापस;

	snम_लिखो(name, माप(name), "%x", ent->type);
	proc_create_single_data(name, S_IFREG | 0444, procdir,
			nubus_proc_rsrc_show,
			nubus_proc_alloc_pde_data(data, 0));
पूर्ण

/*
 * /proc/nubus stuff
 */

व्योम __init nubus_proc_init(व्योम)
अणु
	proc_create_single("nubus", 0, शून्य, nubus_proc_show);
	proc_bus_nubus_dir = proc_सूची_गढ़ो("bus/nubus", शून्य);
	अगर (!proc_bus_nubus_dir)
		वापस;
	proc_create_single("devices", 0, proc_bus_nubus_dir,
			nubus_devices_proc_show);
पूर्ण
