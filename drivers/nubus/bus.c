<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Bus implementation क्रम the NuBus subप्रणाली.
//
// Copyright (C) 2017 Finn Thain

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/list.h>
#समावेश <linux/nubus.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#घोषणा to_nubus_board(d)       container_of(d, काष्ठा nubus_board, dev)
#घोषणा to_nubus_driver(d)      container_of(d, काष्ठा nubus_driver, driver)

अटल पूर्णांक nubus_bus_match(काष्ठा device *dev, काष्ठा device_driver *driver)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक nubus_device_probe(काष्ठा device *dev)
अणु
	काष्ठा nubus_driver *ndrv = to_nubus_driver(dev->driver);
	पूर्णांक err = -ENODEV;

	अगर (ndrv->probe)
		err = ndrv->probe(to_nubus_board(dev));
	वापस err;
पूर्ण

अटल पूर्णांक nubus_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा nubus_driver *ndrv = to_nubus_driver(dev->driver);
	पूर्णांक err = -ENODEV;

	अगर (dev->driver && ndrv->हटाओ)
		err = ndrv->हटाओ(to_nubus_board(dev));
	वापस err;
पूर्ण

काष्ठा bus_type nubus_bus_type = अणु
	.name		= "nubus",
	.match		= nubus_bus_match,
	.probe		= nubus_device_probe,
	.हटाओ		= nubus_device_हटाओ,
पूर्ण;
EXPORT_SYMBOL(nubus_bus_type);

पूर्णांक nubus_driver_रेजिस्टर(काष्ठा nubus_driver *ndrv)
अणु
	ndrv->driver.bus = &nubus_bus_type;
	वापस driver_रेजिस्टर(&ndrv->driver);
पूर्ण
EXPORT_SYMBOL(nubus_driver_रेजिस्टर);

व्योम nubus_driver_unरेजिस्टर(काष्ठा nubus_driver *ndrv)
अणु
	driver_unरेजिस्टर(&ndrv->driver);
पूर्ण
EXPORT_SYMBOL(nubus_driver_unरेजिस्टर);

अटल काष्ठा device nubus_parent = अणु
	.init_name	= "nubus",
पूर्ण;

अटल पूर्णांक __init nubus_bus_रेजिस्टर(व्योम)
अणु
	वापस bus_रेजिस्टर(&nubus_bus_type);
पूर्ण
postcore_initcall(nubus_bus_रेजिस्टर);

पूर्णांक __init nubus_parent_device_रेजिस्टर(व्योम)
अणु
	वापस device_रेजिस्टर(&nubus_parent);
पूर्ण

अटल व्योम nubus_device_release(काष्ठा device *dev)
अणु
	काष्ठा nubus_board *board = to_nubus_board(dev);
	काष्ठा nubus_rsrc *fres, *पंचांगp;

	list_क्रम_each_entry_safe(fres, पंचांगp, &nubus_func_rsrcs, list)
		अगर (fres->board == board) अणु
			list_del(&fres->list);
			kमुक्त(fres);
		पूर्ण
	kमुक्त(board);
पूर्ण

पूर्णांक nubus_device_रेजिस्टर(काष्ठा nubus_board *board)
अणु
	board->dev.parent = &nubus_parent;
	board->dev.release = nubus_device_release;
	board->dev.bus = &nubus_bus_type;
	dev_set_name(&board->dev, "slot.%X", board->slot);
	board->dev.dma_mask = &board->dev.coherent_dma_mask;
	dma_set_mask(&board->dev, DMA_BIT_MASK(32));
	वापस device_रेजिस्टर(&board->dev);
पूर्ण

अटल पूर्णांक nubus_prपूर्णांक_device_name_fn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा nubus_board *board = to_nubus_board(dev);
	काष्ठा seq_file *m = data;

	seq_म_लिखो(m, "Slot %X: %s\n", board->slot, board->name);
	वापस 0;
पूर्ण

पूर्णांक nubus_proc_show(काष्ठा seq_file *m, व्योम *data)
अणु
	वापस bus_क्रम_each_dev(&nubus_bus_type, शून्य, m,
				nubus_prपूर्णांक_device_name_fn);
पूर्ण
