<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RESET_CONTROLLER_H_
#घोषणा _LINUX_RESET_CONTROLLER_H_

#समावेश <linux/list.h>

काष्ठा reset_controller_dev;

/**
 * काष्ठा reset_control_ops - reset controller driver callbacks
 *
 * @reset: क्रम self-deनिश्चितing resets, करोes all necessary
 *         things to reset the device
 * @निश्चित: manually निश्चित the reset line, अगर supported
 * @deनिश्चित: manually deनिश्चित the reset line, अगर supported
 * @status: वापस the status of the reset line, अगर supported
 */
काष्ठा reset_control_ops अणु
	पूर्णांक (*reset)(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id);
	पूर्णांक (*निश्चित)(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id);
	पूर्णांक (*deनिश्चित)(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id);
	पूर्णांक (*status)(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id);
पूर्ण;

काष्ठा module;
काष्ठा device_node;
काष्ठा of_phandle_args;

/**
 * काष्ठा reset_control_lookup - represents a single lookup entry
 *
 * @list: पूर्णांकernal list of all reset lookup entries
 * @provider: name of the reset controller device controlling this reset line
 * @index: ID of the reset controller in the reset controller device
 * @dev_id: name of the device associated with this reset line
 * @con_id: name of the reset line (can be शून्य)
 */
काष्ठा reset_control_lookup अणु
	काष्ठा list_head list;
	स्थिर अक्षर *provider;
	अचिन्हित पूर्णांक index;
	स्थिर अक्षर *dev_id;
	स्थिर अक्षर *con_id;
पूर्ण;

#घोषणा RESET_LOOKUP(_provider, _index, _dev_id, _con_id)		\
	अणु								\
		.provider = _provider,					\
		.index = _index,					\
		.dev_id = _dev_id,					\
		.con_id = _con_id,					\
	पूर्ण

/**
 * काष्ठा reset_controller_dev - reset controller entity that might
 *                               provide multiple reset controls
 * @ops: a poपूर्णांकer to device specअगरic काष्ठा reset_control_ops
 * @owner: kernel module of the reset controller driver
 * @list: पूर्णांकernal list of reset controller devices
 * @reset_control_head: head of पूर्णांकernal list of requested reset controls
 * @dev: corresponding driver model device काष्ठा
 * @of_node: corresponding device tree node as phandle target
 * @of_reset_n_cells: number of cells in reset line specअगरiers
 * @of_xlate: translation function to translate from specअगरier as found in the
 *            device tree to id as given to the reset control ops, शेषs
 *            to :c:func:`of_reset_simple_xlate`.
 * @nr_resets: number of reset controls in this reset controller device
 */
काष्ठा reset_controller_dev अणु
	स्थिर काष्ठा reset_control_ops *ops;
	काष्ठा module *owner;
	काष्ठा list_head list;
	काष्ठा list_head reset_control_head;
	काष्ठा device *dev;
	काष्ठा device_node *of_node;
	पूर्णांक of_reset_n_cells;
	पूर्णांक (*of_xlate)(काष्ठा reset_controller_dev *rcdev,
			स्थिर काष्ठा of_phandle_args *reset_spec);
	अचिन्हित पूर्णांक nr_resets;
पूर्ण;

पूर्णांक reset_controller_रेजिस्टर(काष्ठा reset_controller_dev *rcdev);
व्योम reset_controller_unरेजिस्टर(काष्ठा reset_controller_dev *rcdev);

काष्ठा device;
पूर्णांक devm_reset_controller_रेजिस्टर(काष्ठा device *dev,
				   काष्ठा reset_controller_dev *rcdev);

व्योम reset_controller_add_lookup(काष्ठा reset_control_lookup *lookup,
				 अचिन्हित पूर्णांक num_entries);

#पूर्ण_अगर
