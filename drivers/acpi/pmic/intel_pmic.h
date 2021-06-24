<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __INTEL_PMIC_H
#घोषणा __INTEL_PMIC_H

काष्ठा pmic_table अणु
	पूर्णांक address;	/* operation region address */
	पूर्णांक reg;	/* corresponding thermal रेजिस्टर */
	पूर्णांक bit;	/* control bit क्रम घातer */
पूर्ण;

काष्ठा पूर्णांकel_pmic_opregion_data अणु
	पूर्णांक (*get_घातer)(काष्ठा regmap *r, पूर्णांक reg, पूर्णांक bit, u64 *value);
	पूर्णांक (*update_घातer)(काष्ठा regmap *r, पूर्णांक reg, पूर्णांक bit, bool on);
	पूर्णांक (*get_raw_temp)(काष्ठा regmap *r, पूर्णांक reg);
	पूर्णांक (*update_aux)(काष्ठा regmap *r, पूर्णांक reg, पूर्णांक raw_temp);
	पूर्णांक (*get_policy)(काष्ठा regmap *r, पूर्णांक reg, पूर्णांक bit, u64 *value);
	पूर्णांक (*update_policy)(काष्ठा regmap *r, पूर्णांक reg, पूर्णांक bit, पूर्णांक enable);
	पूर्णांक (*exec_mipi_pmic_seq_element)(काष्ठा regmap *r, u16 i2c_address,
					  u32 reg_address, u32 value, u32 mask);
	काष्ठा pmic_table *घातer_table;
	पूर्णांक घातer_table_count;
	काष्ठा pmic_table *thermal_table;
	पूर्णांक thermal_table_count;
	/* For generic exec_mipi_pmic_seq_element handling */
	पूर्णांक pmic_i2c_address;
पूर्ण;

पूर्णांक पूर्णांकel_pmic_install_opregion_handler(काष्ठा device *dev, acpi_handle handle, काष्ठा regmap *regmap, काष्ठा पूर्णांकel_pmic_opregion_data *d);

#पूर्ण_अगर
