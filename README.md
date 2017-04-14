# unique id

unique id 是php生成唯一ID的扩展 

## Requirement
- PHP 7.0 +

### Compile unique id in Linux

```
$/path/to/phpize
$./configure --with-php-config=/path/to/php-config
$make && make install
```

### DocumentRoot

```php
<?php
//$iden 实例的唯一标识
$id=generate_id($iden);
echo $id;
//反解id
$time = generate_id_time($id); //时间
$iden = generate_id_iden($id); //唯一标识

```
### CLI

```php
[root@e10bffb42e5c etc]# /usr/local/php7/bin/php -c /usr/local/php7/etc/php.ini  -r "echo generate_id(1);"
6246637400135568401
```
