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

ALTER TABLE `receiver`
    ADD CONSTRAINT `receiver_ibfk_1` FOREIGN KEY (`sender_id`) REFERENCES `sender` (`id`);
