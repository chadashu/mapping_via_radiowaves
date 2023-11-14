CREATE TABLE `sender` (
                          `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
                          `frequency` FLOAT NOT NULL,
                          `geolocation` POINT NOT NULL,
                          `created_at` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                          `ip_address` VARCHAR(255) NOT NULL
);

CREATE TABLE `receiver` (
                            `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
                            `sender_id` INTEGER NOT NULL,
                            `frequency` FLOAT NOT NULL,
                            `geolocation` POINT NOT NULL,
                            `created_at` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
                            `ip_address` VARCHAR(255) NOT NULL
);

CREATE TABLE `training_data` (
                                 `id` INTEGER PRIMARY KEY AUTO_INCREMENT,
                                 `frequency` INTEGER NOT NULL,
                                 `materials` TEXT DEFAULT NULL,
                                 `thickness` DECIMAL(16,2) DEFAULT NULL,
                                 `distance` DECIMAL(10,5) DEFAULT NULL,
                                 `rssi` INTEGER NOT NULL,
                                 `created_at` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
);

ALTER TABLE `receiver`
    ADD CONSTRAINT `receiver_ibfk_1` FOREIGN KEY (`sender_id`) REFERENCES `sender` (`id`);
