#include <linux/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <i2c.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

struct device_info {
	char *name;
	char *package;
	uint64_t id;
};

struct device_info gen1_devices[] = {
	{"ISL68124",	"40 LD QFN",	0x1E},
	{"ISL68127",	"48 LD QFN",	0x28},
	{"ISL68134",	"40 LD QFN",	0x1F},
	{"ISL68137",	"48 LD QFN",	0x27},
	{"ISL68144",	"40 LD QFN",	0x22},
	{"ISL68147",	"48 LD QFN",	0x29},
	{"ISL69122",	"40 LD QFN",	0x2E},
	{"ISL69124",	"40 LD QFN",	0x2B},
	{"ISL69125",	"40 LD QFN",	0x2C},
	{"ISL69127",	"48 LD QFN",	0x23},
	{"ISL69128",	"48 LD QFN",	0x24},
	{"ISL69129",	"48 LD QFN",	0x2A},
	{"ISL69133",	"40 LD QFN",	0x30},
	{"ISL69134",	"40 LD QFN",	0x2D},
	{"ISL69137",	"48 LD QFN",	0x25},
	{"ISL69138",	"48 LD QFN",	0x31},
	{"ISL69144",	"40 LD QFN",	0x2F},
	{"ISL69147",	"48 LD QFN",	0x26},
	{"ISL69158",	"48 LD QFN",	0x32},
	{NULL, NULL, 0}
};

struct device_info gen2_devices[] = {
	{"ISL68220",	"32 LD QFN",	0x63},
	{"ISL68221",	"40 LD QFN",	0x62},
	{"ISL68222",	"40 LD QFN",	0x61},
	{"ISL68223",	"40 LD QFN",	0x53},
	{"ISL68224",	"52 LD QFN",	0x52},
	{"ISL68225",	"52 LD QFN",	0x51},
	{"ISL68226",	"60 LD QFN",	0x50},
	{"ISL68227",	"60 LD QFN",	0x4F},
	{"ISL68229",	"68 LD QFN",	0x4E},
	{"ISL68233",	"40 LD QFN",	0x6B},
	{"ISL68236",	"52 LD QFN",	0x4D},
	{"ISL68239",	"68 LD QFN",	0x4B},
	{"ISL69222",	"32 LD QFN",	0x3E},
	{"ISL69223",	"40 LD QFN",	0x3D},
	{"ISL69224",	"40 LD QFN",	0x3C},
	{"ISL69225",	"40 LD QFN",	0x3B},
	{"ISL69227",	"52 LD QFN",	0x3A},
	{"ISL69228",	"52 LD QFN",	0x39},
	{"ISL69234",	"40 LD QFN",	0x43},
	{"ISL69236",	"52 LD QFN",	0x42},
	{"ISL69237",	"52 LD QFN",	0x66},
	{"ISL69239",	"60 LD QFN",	0x41},
	{"ISL69242",	"32 LD QFN",	0x58},
	{"ISL69243",	"32 LD QFN",	0x59},
	{"ISL69247",	"52 LD QFN",	0x48},
	{"ISL69248",	"60 LD QFN",	0x47},
	{"ISL69249",	"68 LD QFN",	0x6D},
	{"ISL69254",	"40 LD QFN",	0x67},
	{"ISL69255",	"52 LD QFN",	0x38},
	{"ISL69256",	"52 LD QFN",	0x37},
	{"ISL69259",	"40 LD QFN",	0x46},
	{"ISL69260",	"40 LD QFN",	0x6E},
	{"ISL69268",	"60 LD QFN",	0x3F},
	{"ISL69269",	"68 LD QFN",	0x55},
	{NULL, NULL, 0}
};

struct device_info gen3_devices[] = {
	{"ISL69260",	"40 LD QFN",	0x81},
	{"RAA228113",	"32 LD QFN",	0x90},
	{"RAA228234",	"40 LD QFN",	0xAF},
	{"RAA228236",	"48 LD QFN",	0xAE},
	{"RAA228924",	"48 LD QFN",	0x8F},
	{"RAA228926",	"68 LD QFN",	0x8E},
	{"RAA228928",	"56 LD QFN",	0xB4},
	{"RAA228929",	"48 LD QFN",	0xB2},
	{"RAA228930",	"40 LD QFN",	0xB3},
	{"RAA228931",	"40 LD QFN",	0xB5},
	{"RAA228932",	"56 LD QFN",	0xB6},
	{"RAA229126",	"48 LD QFN",	0x82},
	{"RAA229130",	"68 LD QFN",	0x97},
	{"RAA229131",	"68 LD QFN",	0x98},
	{"RAA229132",	"40 LD QFN",	0x96},
	{"RAA229325",	"48 LD QFN",	0x88},
	{"RAA229613",	"32 LD QFN",	0x8A},
	{"RAA229620",	"48 LD QFN",	0x9B},
	{"RAA229621",	"40 LD QFN",	0x9C},
	{"RAA229625",	"48 LD QFN",	0x8B},
	{"RAA229628",	"68 LD QFN",	0x8D},
	{"RAA229629",	"56 LD QFN",	0xA4},
	{"RAA229631",	"40 LD QFN",	0xA2},
	{"RAA229638",	"68 LD QFN",	0x9D},
	{"RAA229724",	"40 LD QFN",	0x7F},
	{"RAA229725",	"40 LD QFN",	0xB1},
	{"RAA229726",	"48 LD QFN",	0x80},
	{"RAA229817",	"52 LD QFN",	0x86},
	{"RAA229828",	"68 LD QFN",	0x87},
	{NULL, NULL, 0}
};

struct category_info {
	char *name;
	struct device_info *device_list;

	int set_dma_addr_cmd;
	int get_dma_data_cmd;
	int apply_settings_cmd;

	int nvm_slot_num_reg;
	int voltage_regulation_enable;
	int check_program_result_reg;
	int bank_status_reg;
};

struct category_info cat_info[] = {
	/* gen1, isl68127 */
	{"Gen1", gen1_devices, 0xF7, 0xF5, 0xE7, 0x1080, 0x106d, 0x1400, 0x1401},
	/* gen2, isl68224 */
	{"Gen2", gen2_devices, 0xC7, 0xC5, -1,   0xC2, -1, 0x0707, 0x0709},
	/* gen3, raa228236 */
	{"Gen3", gen3_devices, 0xC7, 0xC5, 0xE7,   0x35, -1, 0x007E, 0x007F},
};

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof((a)[0]))

struct pmic_device {
	int fd;
	int bus;
	int addr;
	int id;
	uint64_t reversion;

	int avl_nvm_slot_num;

	struct category_info *cat;
	struct device_info *info;
};

#define CMD_DEVICE_ID	0xad
#define CMD_REVERSION	0xae

int get_device_id_reversion(struct pmic_device *dev)
{
	uint8_t tmp[8];
	int err;
	int i;
	uint8_t id_size;

	/* device id format, [size] [LSB0] [LSB1] [LSB2] ... */
	err = i2c_smbus_read_i2c_block_data(dev->fd, CMD_DEVICE_ID, 1, &id_size);
	if (err < 0) {
		fprintf(stderr, "Device 0x%x on bus %d doesn't exist\n", dev->addr, dev->bus);
		return err;
	}

	if (id_size > sizeof(tmp)) {
		fprintf(stderr, "Device ID too long, anounced %d bytes, exceed %lu bytes\n",
				id_size, sizeof(tmp));
	}

	/* include size byte */
	err = i2c_smbus_read_i2c_block_data(dev->fd, CMD_DEVICE_ID, id_size + 1, tmp);
	if (err < 0) {
		fprintf(stderr, "Cannot get ID from device 0x%02x on bus %d\n",
				dev->addr, dev->bus);
		return err;
	}

	dev->id = tmp[2];

	/* get reversion */
	err = i2c_smbus_read_i2c_block_data(dev->fd, CMD_REVERSION, 1, &id_size);
	if (err < 0) {
		fprintf(stderr, "Device 0x%x on bus %d IO error\n", dev->addr, dev->bus);
		return err;
	}

	if (id_size > sizeof(tmp)) {
		fprintf(stderr, "Reversion too long, anounced %d bytes, exceed %lu bytes\n",
				id_size, sizeof(tmp));
	}

	/* include size byte */
	err = i2c_smbus_read_i2c_block_data(dev->fd, CMD_REVERSION, id_size + 1, tmp);
	if (err < 0) {
		fprintf(stderr, "Cannot get reversion from device 0x%02x on bus %d\n",
				dev->addr, dev->bus);
		return err;
	}

	dev->reversion = 0;
	for (i = 1; i < id_size + 1; ++i)
		dev->reversion |= tmp[i] << (8 * (i - 1));

	return 0;
}

void show_device_info(struct pmic_device *dev)
{
	printf("Slave Address(7bit): 0x%02x\n", dev->addr);
	printf("On SoC Bus: %d\n", dev->bus);
	printf("Device ID: %X\n", dev->id);
	printf("Reversion: %lX\n", dev->reversion);
	printf("Device Category: %s\n", dev->cat->name);
	printf("Product: %s\n", dev->info->name);
	printf("Package: %s\n", dev->info->package);
	printf("Available NVM Slot Number: %d\n", dev->avl_nvm_slot_num);
}

static int i2c_bus_init(struct pmic_device *dev, int bus, int addr)
{
	int fd;
	char dev_name[16];

	snprintf(dev_name, sizeof(dev_name), "/dev/i2c-%d", bus);
	fd = open(dev_name, O_RDONLY);
	if (fd < 0) {
		printf("open i2c device failed\n");
		return -1;
	}
	int err;
	err = ioctl(fd, I2C_SLAVE_FORCE, addr);
	if (err < 0) {
		printf("failed to set i2c slave address\n");
		close(fd);
		return -1;
	}

	dev->fd = fd;
	dev->bus = bus;
	dev->addr = addr;

	return fd;
}

static void i2c_bus_destroy(struct pmic_device *dev)
{
	close(dev->fd);
}

int setup_category(struct pmic_device *dev)
{
	int i;
	struct category_info *cat;
	struct device_info *info;

	dev->cat = NULL;
	dev->info = NULL;

	/* find category in device list */
	for (i = 0; i < ARRAY_SIZE(cat_info); ++i) {
		cat = &cat_info[i];
		/* find in this category */
		for (info = cat->device_list; info->name; ++info) {
			if (info->id == dev->id) {
				dev->cat = cat;
				dev->info = info;
				return 0;
			}
		}
	}

	return -ENODEV;
}

int isl68224_get_dma_data(struct pmic_device *dev, uint16_t addr, unsigned int len, uint8_t *data)
{
	int err;
	uint8_t tmp[2];
	struct category_info *cat;

	cat = dev->cat;

	tmp[0] = addr & 0xff;
	tmp[1] = (addr >> 8) & 0xff;

	err = i2c_smbus_write_i2c_block_data(dev->fd, cat->set_dma_addr_cmd, sizeof(tmp), tmp);
	if (err) {
		fprintf(stderr, "failed to set dma address\n");
		return err;
	}

	return i2c_smbus_read_i2c_block_data(dev->fd, cat->get_dma_data_cmd, len, data);
}

unsigned int get_available_nvm_slot_number(struct pmic_device *dev)
{
	uint8_t tmp[4];
	uint32_t num;
	struct category_info *cat;

	cat = dev->cat;

	isl68224_get_dma_data(dev, cat->nvm_slot_num_reg, sizeof(tmp), tmp);

	num = tmp[0] | (tmp[1] << 8) | (tmp[2] << 16) | (tmp[3] << 24);

	dev->avl_nvm_slot_num = num;

	return num;
}

int isl68224_enable_voltage_regulation(struct pmic_device *dev)
{
	uint8_t tmp[4];
	uint8_t data[2];
	data[0] = 0x01;
	data[1] = 0x00;
	int err;
	struct category_info *cat;

	cat = dev->cat;

	if (cat->voltage_regulation_enable < 0)
		return 0;

	isl68224_get_dma_data(dev, cat->voltage_regulation_enable, sizeof(tmp), tmp);
	tmp[0] |= (1 << 0);
	err = i2c_smbus_write_i2c_block_data(dev->fd, cat->get_dma_data_cmd, sizeof(tmp), tmp);
	if (err){
		printf("err = %d\n", err);
		return err;
	}

	return i2c_smbus_write_i2c_block_data(dev->fd, cat->apply_settings_cmd, sizeof(data), data);
}

unsigned int isl68224_check_program_result(struct pmic_device *dev)
{
	uint8_t tmp[4];
	int err;
	struct category_info *cat;

	cat = dev->cat;

	err = isl68224_get_dma_data(dev, cat->check_program_result_reg, sizeof(tmp), tmp);
	if (err){
		printf("get program status failed\n");
		return 0;
	}

	return tmp[0];
}

int isl68224_get_bank_status_reg(struct pmic_device *dev)
{
	uint8_t tmp[4];
	int err;
	struct category_info *cat;

	cat = dev->cat;

	err = isl68224_get_dma_data(dev, cat->bank_status_reg, sizeof(tmp), tmp);
	if (err){
		printf("get bank status failed\n");
		return err;
	}

	return 0;
}

static int hex2bin(char hex)
{
	if (hex >= '0' && hex <= '9')
		return hex - '0';
	else if (hex >= 'a' && hex <= 'f')
		return hex - 'a' + 10;
	else if (hex >= 'A' && hex <= 'F')
		return hex - 'A' + 10;
	else
		return -EINVAL;
}

int isl68224_program(struct pmic_device *dev, int addr, char *name)
{
	struct stat st;
	int err;
	char *hex;
	ssize_t size;

	int i, j, status_reg;
	int tag, nb, cmd;//, pa, crc;
	// int tag, nb, cmd, pa, crc;
	uint8_t line_buf[64];
	int line_size;
	uint8_t data_buf[32];
	uint8_t write_buf[32];
	int data_size;

	err = stat(name, &st);
	if (err) {
		fprintf(stderr, "cannot get file status\n");
		return err;
	}

	hex = malloc(st.st_size + 1);

	if (!hex) {
		fprintf(stderr, "allocate buffer failed\n");
		return -ENOMEM;
	}

	int fd = open(name, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "cannot open file %s\n", name);
		return fd;
	}

	size = read(fd, hex, st.st_size);
	close(fd);
	if (size != st.st_size) {
		fprintf(stderr, "cannot get enough data\n");
		goto free_buf;
	}

	hex[st.st_size] = 0;
	
	for (i = 0; i < st.st_size; ++i) {
		for (line_size = 0; i < st.st_size; ++i) {
			if (line_size > sizeof(line_buf)) {
				fprintf(stderr, "hex string too long\n");
				goto free_buf;
			}

			if (hex[i] == '\n')
				break;
			else if (isxdigit(hex[i]))
				line_buf[line_size++] = hex[i];
		}

		/* empty line */
		if (line_size == 0)
			continue;

		if (line_size % 2) {
			fprintf(stderr, "wrong hex number per line\n");
			goto free_buf;
		}

		/* convert hex string to binary */
		for (j = 0; j < line_size; j += 2) {
			data_buf[j / 2] = hex2bin(line_buf[j]) << 4 |
				hex2bin(line_buf[j + 1]);
		}
		data_size = line_size / 2;

		if (data_size < 2) {
			fprintf(stderr, "wrong format: line too short\n");
			goto free_buf;
		}

		tag = data_buf[0];
		nb = data_buf[1];

		if (nb + 2 != data_size) {
			fprintf(stderr, "wrong format: invalid byte count\n");
			goto free_buf;
		}

		if (tag != 0)
			/* skip lines that shouldnot burn into device */
			continue;

		if (nb < 3) {
			fprintf(stderr, "wrong format: invalid byte count\n");
			goto free_buf;
		}

		// pa = data_buf[2];
		cmd = data_buf[3];

		/* ignore, we donnot use PEC */
		// crc = data_buf[data_size - 1];

		// printf("%02X", tag);
		// printf("%02X", nb);
		// printf("%02X", pa);
		// printf("%02X", cmd);

		for (int k = 0; k < nb - 3; ++k){
			// printf("%02X", data_buf[4 + i]);
			write_buf[k] = data_buf[4 + k];
		}

		// printf("%02X", crc);
		// printf("\n");
		printf("  programming... %ld%%\r", (i + 1) * 100 / st.st_size);

		i2c_smbus_write_i2c_block_data(dev->fd, cmd, nb - 3, write_buf);
	}

	printf("\n");

	sleep(1);

	status_reg = isl68224_check_program_result(dev);
	if (status_reg & (1 << 0))
		printf("Program seccess\n");
	else
		printf("Program failed! status reg= 0x%x\n", status_reg);

	isl68224_get_bank_status_reg(dev);

free_buf:
	free(hex);

	return 0;
}

static const char * const script_usage_info =
	"isl-util i2c-bus slave-addr [filename]";

int main(int argc, char *argv[])
{
	struct pmic_device dev;
	int bus;
	int addr;
	int fd;
	int err;

	if (argc < 3 || argc > 4) {
		printf("%s\n", script_usage_info);
		return -1;
	}

	bus = strtol(argv[1], NULL, 0);

	addr = strtol(argv[2], NULL, 0);

	fd = i2c_bus_init(&dev, bus, addr);
	if (fd < 0)
		return -1;

	err = get_device_id_reversion(&dev);
	if (err)
		return -err;

	err = setup_category(&dev);
	if (err) {
		fprintf(stderr, "Device ID %d not found in supported list\n", dev.id);
		return -err;
	}

	get_available_nvm_slot_number(&dev);

	show_device_info(&dev);

	if (argc == 3)
		return 0;

	isl68224_enable_voltage_regulation(&dev);
	sleep(1);

	isl68224_program(&dev, addr, argv[3]);

	i2c_bus_destroy(&dev);
	return 0;
}

