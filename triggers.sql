CREATE TRIGGER CA_insert BEFORE INSERT ON CAs FOR EACH ROW SET NEW.createtime = NOW();
CREATE TRIGGER address_insert BEFORE INSERT ON addresses FOR EACH ROW SET NEW.createtime = NOW();
CREATE TRIGGER badge_insert BEFORE INSERT ON badges FOR EACH ROW SET NEW.createtime = NOW();
CREATE TRIGGER donation_insert BEFORE INSERT ON donations FOR EACH ROW SET NEW.createtime = NOW();
CREATE TRIGGER food_insert BEFORE INSERT ON food FOR EACH ROW SET NEW.createtime = NOW();
CREATE TRIGGER inventory_insert BEFORE INSERT ON inventory FOR EACH ROW SET NEW.createtime = NOW();
CREATE TRIGGER merchandise_insert BEFORE INSERT ON merchandise FOR EACH ROW SET NEW.createtime = NOW();
CREATE TRIGGER transaction_insert BEFORE INSERT ON transactions FOR EACH ROW SET NEW.createtime = NOW();
