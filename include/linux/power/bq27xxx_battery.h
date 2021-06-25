<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_BQ27X00_BATTERY_H__
#घोषणा __LINUX_BQ27X00_BATTERY_H__

क्रमागत bq27xxx_chip अणु
	BQ27000 = 1, /* bq27000, bq27200 */
	BQ27010, /* bq27010, bq27210 */
	BQ2750X, /* bq27500 deprecated alias */
	BQ2751X, /* bq27510, bq27520 deprecated alias */
	BQ2752X,
	BQ27500, /* bq27500/1 */
	BQ27510G1, /* bq27510G1 */
	BQ27510G2, /* bq27510G2 */
	BQ27510G3, /* bq27510G3 */
	BQ27520G1, /* bq27520G1 */
	BQ27520G2, /* bq27520G2 */
	BQ27520G3, /* bq27520G3 */
	BQ27520G4, /* bq27520G4 */
	BQ27521, /* bq27521 */
	BQ27530, /* bq27530, bq27531 */
	BQ27531,
	BQ27541, /* bq27541, bq27542, bq27546, bq27742 */
	BQ27542,
	BQ27546,
	BQ27742,
	BQ27545, /* bq27545 */
	BQ27411,
	BQ27421, /* bq27421, bq27441, bq27621 */
	BQ27425,
	BQ27426,
	BQ27441,
	BQ27621,
	BQ27Z561,
	BQ28Z610,
	BQ34Z100,
	BQ78Z100,
पूर्ण;

काष्ठा bq27xxx_device_info;
काष्ठा bq27xxx_access_methods अणु
	पूर्णांक (*पढ़ो)(काष्ठा bq27xxx_device_info *di, u8 reg, bool single);
	पूर्णांक (*ग_लिखो)(काष्ठा bq27xxx_device_info *di, u8 reg, पूर्णांक value, bool single);
	पूर्णांक (*पढ़ो_bulk)(काष्ठा bq27xxx_device_info *di, u8 reg, u8 *data, पूर्णांक len);
	पूर्णांक (*ग_लिखो_bulk)(काष्ठा bq27xxx_device_info *di, u8 reg, u8 *data, पूर्णांक len);
पूर्ण;

काष्ठा bq27xxx_reg_cache अणु
	पूर्णांक temperature;
	पूर्णांक समय_प्रकारo_empty;
	पूर्णांक समय_प्रकारo_empty_avg;
	पूर्णांक समय_प्रकारo_full;
	पूर्णांक अक्षरge_full;
	पूर्णांक cycle_count;
	पूर्णांक capacity;
	पूर्णांक energy;
	पूर्णांक flags;
	पूर्णांक health;
पूर्ण;

काष्ठा bq27xxx_device_info अणु
	काष्ठा device *dev;
	पूर्णांक id;
	क्रमागत bq27xxx_chip chip;
	u32 opts;
	स्थिर अक्षर *name;
	काष्ठा bq27xxx_dm_reg *dm_regs;
	u32 unseal_key;
	काष्ठा bq27xxx_access_methods bus;
	काष्ठा bq27xxx_reg_cache cache;
	पूर्णांक अक्षरge_design_full;
	अचिन्हित दीर्घ last_update;
	काष्ठा delayed_work work;
	काष्ठा घातer_supply *bat;
	काष्ठा list_head list;
	काष्ठा mutex lock;
	u8 *regs;
पूर्ण;

व्योम bq27xxx_battery_update(काष्ठा bq27xxx_device_info *di);
पूर्णांक bq27xxx_battery_setup(काष्ठा bq27xxx_device_info *di);
व्योम bq27xxx_battery_tearकरोwn(काष्ठा bq27xxx_device_info *di);

#पूर्ण_अगर
